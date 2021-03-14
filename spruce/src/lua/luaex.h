#pragma once
#include "core.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "parameters.h"
#include "helpers.h"

namespace spr {

    template<typename T>
    class LuaClass;

    static void* LuaAlloc(void* ud, void* ptr, size_t osize, size_t nsize) {
        (void)ud; (void)osize;  /* not used */
        if (nsize == 0) {
            //free(ptr);
            delete ptr;
            return NULL;
        }
        else
            return realloc(ptr, nsize);
    }

    class Lua {
    public:
        static void Init() {
            L = lua_newstate(LuaAlloc, nullptr);

            LoadDefinitions();
        }

        static void Dispose() {
            lua_close(L);
        }

        SPR_API static void LoadDefinitions();

        static void Run(const std::string& src) {
            int err = luaL_dostring(L, src.c_str());
            if (err != LUA_OK) {
                spr::Console::LogError("LUA ERROR:\n", lua_tostring(L, -1));
            }
        }

        template<typename T>
        static T Get(const std::string& name) {
            lua_getglobal(L, name.c_str());
            return LuaParameter<T>::Get(L, -1);
        }

        static void* GetUserData(const std::string& name) {
            lua_getglobal(L, name.c_str());
            Lua::DumpStack();
            return lua_touserdata(L, -1);
        }

        static void DumpStack() {
            int top = lua_gettop(L);
            for (int i = 1; i <= top; i++) {
                printf("%d\t%s\t", i, luaL_typename(L, i));
                switch (lua_type(L, i)) {
                case LUA_TNUMBER:
                    printf("%g\n", lua_tonumber(L, i));
                    break;
                case LUA_TSTRING:
                    printf("%s\n", lua_tostring(L, i));
                    break;
                case LUA_TBOOLEAN:
                    printf("%s\n", (lua_toboolean(L, i) ? "true" : "false"));
                    break;
                case LUA_TNIL:
                    printf("%s\n", "nil");
                    break;
                default:
                    printf("%p\n", lua_topointer(L, i));
                    break;
                }
            }
            printf("\n");
        }

        static lua_State* GetState() { return L; }

        static std::string GetMetaTableName(const std::string& className) { return "Classes." + className; }
        static std::string GetGetterName(const std::string& name) { return std::string("Get") + (char)std::toupper(name[0]) + &name[1]; }
        static std::string GetSetterName(const std::string& name) { return std::string("Set") + (char)std::toupper(name[0]) + &name[1]; }

        template<typename T>
        static const void* GetClassRegistry() { static char value; return &value; }

        static void TableRawSetField(lua_State* L, const std::string& key, int index) {
            index = lua_absindex(L, -2);
            lua_pushstring(L, key.c_str());
            lua_insert(L, -2);
            lua_rawset(L, index);
        }

    private:
        SPR_API static lua_State* L;
    };

    template<typename T>
    class LuaClass {
    public:
        LuaClass(const std::string& name) : name(name) {
            lua_State* L = Lua::GetState();
            const char* className = name.c_str();

            lua_newtable(L);
            lua_pushvalue(L, -1);
            lua_setmetatable(L, -2);
            lua_pushvalue(L, -1);
            lua_setglobal(L, className);

            lua_pushstring(L, "__index");
            lua_pushcclosure(L, LuaClassIndexMetaMethod<T>::f, 0);
            lua_settable(L, -3);

            lua_pushstring(L, "__newindex");
            lua_pushcclosure(L, LuaClassNewIndexMetaMethod<T>::f, 0);
            lua_settable(L, -3);

            lua_pushvalue(L, -1);
            lua_rawsetp(L, LUA_REGISTRYINDEX, Lua::GetClassRegistry<T>());
        }

        template<typename ... Args>
        LuaClass<T>& AddConstructor() {
            lua_State* L = Lua::GetState();

            //lua_pushstring(L, name.c_str());
            lua_pushcclosure(L, LuaClassContructor<T, Args...>::f, 0);
            Lua::TableRawSetField(L, "__call", -2);

            return *this;
        }

        LuaClass<T>& AddDestructor() {
            lua_State* L = Lua::GetState();

            lua_pushcclosure(L, LuaClassDestructor<T>::f, 0);
            Lua::TableRawSetField(L, "__gc", -2);

            return *this;
        }

        template<typename Ret, typename ... Args>
        LuaClass<T>& AddFunction(const std::string& name, Ret(T::* f) (Args...) const) {
            return AddFunction<Ret, Args...>(name, (Ret(T:: *) (Args...))f);
        }

        template<typename Ret, typename ... Args>
        LuaClass<T>& AddFunction(const std::string& name, Ret (T::*f) (Args...)) {
            lua_State* L = Lua::GetState();

            using Fn = Ret(T::*) (Args...);
            
            new (lua_newuserdata(L, sizeof(Fn))) Fn(f);
            lua_pushcclosure(L, LuaClassFunctionCaller<T, Ret, Args...>::f, 1);
            Lua::TableRawSetField(L, name, -2);

            return *this;
        }

        template<typename U>
        LuaClass<T>& AddProperty(const std::string& name, U T::*p) {
            lua_State* L = Lua::GetState();

            using Pr = const U T::*;

            new (lua_newuserdata(L, sizeof(Pr))) Pr(p);
            lua_pushcclosure(L, LuaClassPropertyGetter<T, U>::f, 1);
            Lua::TableRawSetField(L, Lua::GetGetterName(name.c_str()), -2);

            new (lua_newuserdata(L, sizeof(Pr))) Pr(p);
            lua_pushcclosure(L, LuaClassPropertySetter<T, U>::f, 1);
            Lua::TableRawSetField(L, Lua::GetSetterName(name.c_str()), -2);

            return *this;
        }

    private:
        std::string name;       
    };
}