#pragma once
#include "core.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

namespace spr {

    template<typename T>
    struct LuaClassIndexMetaMethod {
        static int f(lua_State* L) {
            const char* index = lua_tostring(L, -1);
            
            lua_getmetatable(L, 1);
            lua_pushvalue(L, 2);
            lua_rawget(L, -2);

            if (lua_iscfunction(L, -1)) {
                return 1;
            }

            lua_pop(L, 1);
            lua_remove(L, 2);
            lua_pushstring(L, Lua::GetGetterName(index).c_str());
            lua_rawget(L, -2);

            if (lua_iscfunction(L, -1)) {
                lua_pushvalue(L, 1);
                lua_call(L, 1, 1);
                return 1;
            }
            luaL_error(L, ("attempt to get unknown property '" + std::string(index) + "'").c_str());
            return 1;
        }
    };

    template<typename T>
    struct LuaClassNewIndexMetaMethod {
        static int f(lua_State* L) {
            const char* index = lua_tostring(L, 2);
            const char* value = lua_tostring(L, 3);
            lua_getmetatable(L, 1);

            lua_pushvalue(L, 2);
            lua_rawget(L, -2);

            if (lua_iscfunction(L, -1)) {
                return 0;
            }

            lua_pop(L, 1);
            lua_remove(L, 2);
            lua_pushstring(L, Lua::GetSetterName(index).c_str());
            lua_rawget(L, -2);

            if (lua_iscfunction(L, -1)) {
                lua_pushvalue(L, 1);
                lua_pushvalue(L, 2);
                lua_call(L, 2, 0);
                return 0;
            }
            luaL_error(L, ("attempt to set unknown property '" + std::string(index) + "'").c_str());
            return 0;
        }
    };

    template<typename T, typename ... Args>
    struct LuaClassContructor {
        static int f(lua_State* L) {
            volatile int idx = sizeof...(Args) + 1;

            void* ptr = lua_newuserdata(L, sizeof(T));
            new (ptr) T((LuaParameterPack<Args>::Get(L, idx--))...);

            lua_getmetatable(L, 1);
            ASSERT(lua_istable(L, -1), "Metatable is not a table!");
            lua_setmetatable(L, -2);
            return 1;
        }
    };

    template<typename T>
    struct LuaClassDestructor {
        static int f(lua_State* L) {
            T* ptr = (T*)lua_touserdata(L, 1);
            ptr->~T();
            return 0;
        }
    };

    // Return value
    template<typename T, typename Ret, typename ... Args>
    struct LuaClassFunctionCaller {
        static int f(lua_State* L) {
            using Fn = Ret(T::*) (Args...);
            volatile int idx = (sizeof...(Args)) + 1;

            T* ptr = (T*)lua_touserdata(L, 1);
            void* fn = lua_touserdata(L, lua_upvalueindex(1));
            LuaParameter<Ret>::Set(L, (ptr->* * (Fn*)fn)((LuaParameterPack<Args>::Get(L, idx--))...));
            lua_rawgetp(L, LUA_REGISTRYINDEX, Lua::GetClassRegistry<Ret>());
            lua_setmetatable(L, -2);
            return 1;
        }
    };

    // Return reference
    template<typename T, typename Ret, typename ... Args>
    struct LuaClassFunctionCaller<T, Ret&, Args...> {
        static int f(lua_State* L) {
            using Fn = Ret&(T::*) (Args...);
            volatile int idx = (sizeof...(Args)) + 1;

            T* ptr = (T*)lua_touserdata(L, 1);
            void* fn = lua_touserdata(L, lua_upvalueindex(1));
            LuaParameter<Ret&>::Set(L, (ptr->* * (Fn*)fn)((LuaParameterPack<Args>::Get(L, idx--))...));
            lua_rawgetp(L, LUA_REGISTRYINDEX, Lua::GetClassRegistry<Ret>());
            Lua::DumpStack();
            lua_setmetatable(L, -2);
            return 1;
        }
    };

    // Return void
    template<typename T, typename ... Args>
    struct LuaClassFunctionCaller<T, void, Args...> {
        static int f(lua_State* L) {
            using Fn = void(T::*) (Args...);
            volatile int idx = (sizeof...(Args)) + 1;

            T* ptr = (T*)lua_touserdata(L, 1);
            void* fn = lua_touserdata(L, lua_upvalueindex(1));

            (ptr->* * (Fn*)fn)((LuaParameterPack<Args>::Get(L, idx--))...);
            return 0;
        }
    };


    // Getter for values and references
    template<typename T, typename U>
    struct LuaClassPropertyGetter {
        static int f(lua_State* L) {
            T* ptr = (T*)lua_touserdata(L, -1);
            U T::** p = static_cast<U T::**>(lua_touserdata(L, lua_upvalueindex(1)));
            LuaParameter<U&>::Set(L, ptr->* * p);
            lua_rawgetp(L, LUA_REGISTRYINDEX, Lua::GetClassRegistry<U>());
            lua_setmetatable(L, -2);
            return 1;
        }
    };

    // Getter for pointers
    template<typename T, typename U>
    struct LuaClassPropertyGetter<T, U*> {
        static int f(lua_State* L) {
            T* ptr = (T*)lua_touserdata(L, -1);
            U T::** p = static_cast<U T::**>(lua_touserdata(L, lua_upvalueindex(1))); // ! This is not working for some reason...
            LuaParameter<U*>::Set(L, &(ptr->* * p));
            lua_rawgetp(L, LUA_REGISTRYINDEX, Lua::GetClassRegistry<U>());
            lua_setmetatable(L, -2);
            return 1;
        }
    };

    template<typename T, typename U>
    struct LuaClassPropertySetter {
        static int f(lua_State* L) {
            T* ptr = (T*)lua_touserdata(L, -2);
            U T::** p = static_cast<U T::**>(lua_touserdata(L, lua_upvalueindex(1)));
            ptr->** p = LuaParameter<U>::Get(L, -1);
            return 0;
        }
    };

}