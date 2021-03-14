#pragma once
#include "core.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <string>

namespace spr {

    template<typename T>
    struct LuaParameter {
        static T Get(lua_State* L, int idx) {
            return *((T*)(lua_touserdata(L, idx)));
        }

        static void Set(lua_State* L, const T& value) {
            void* ptr = lua_newuserdata(L, sizeof(T));
            *((T*)ptr) = value;
        }
    };

    template<typename T>
    struct LuaParameter<T&>{
        static T& Get(lua_State* L, int idx) {
            return *((T*)(lua_touserdata(L, idx)));
        }

        static void LuaParameter<T&>::Set(lua_State* L, const T& value) {
            lua_pushlightuserdata(L, (void*)&value);
        }
    };

    template<typename T>
    struct LuaParameter<T*> {
        static T* Get(lua_State* L, int idx) {
            return (T*)(lua_touserdata(L, idx));
        }

        static void LuaParameter<T*>::Set(lua_State* L, T* value) {
            lua_pushlightuserdata(L, (void*)value);
        }
    };

    template<>
    static int LuaParameter<int>::Get(lua_State* L, int idx) {
        return (int)lua_tonumber(L, idx);
    }
    template<>
    static float LuaParameter<float>::Get(lua_State* L, int idx) {
        return (float)lua_tonumber(L, idx);
    }
    template<>
    static double LuaParameter<double>::Get(lua_State* L, int idx) {
        return (double)lua_tonumber(L, idx);
    }
    template<>
    static uint32 LuaParameter<uint32>::Get(lua_State* L, int idx) {
        return (uint32)lua_tonumber(L, idx);
    }
    template<>
    static std::string LuaParameter<std::string>::Get(lua_State* L, int idx) {
        return std::string(lua_tostring(L, idx));
    }
    template<>
    static const std::string& LuaParameter<const std::string&>::Get(lua_State* L, int idx) {
        return std::string(lua_tostring(L, idx));
    }
    template<>
    static const char* LuaParameter<const char*>::Get(lua_State* L, int idx) {
        return lua_tostring(L, idx);
    }
    template<>
    static bool LuaParameter<bool>::Get(lua_State* L, int idx) {
        return (bool)lua_toboolean(L, idx);
    }

    template<>
    static void LuaParameter<int>::Set(lua_State* L, const int& value) {
        lua_pushnumber(L, (lua_Number)value);
    }
    template<>
    static void LuaParameter<float>::Set(lua_State* L, const float& value) {
        lua_pushnumber(L, (lua_Number)value);
    }
    template<>
    static void LuaParameter<double>::Set(lua_State* L, const double& value) {
        lua_pushnumber(L, (lua_Number)value);
    }
    template<>
    static void LuaParameter<uint32>::Set(lua_State* L, const uint32& value) {
        lua_pushnumber(L, (lua_Number)value);
    }
    template<>
    static void LuaParameter<std::string>::Set(lua_State* L, const std::string& value) {
        lua_pushstring(L, value.c_str());
    }
    template<>
    static void LuaParameter<const char*>::Set(lua_State* L, const char* value) {
        lua_pushstring(L, value);
    }
    template<>
    static void LuaParameter<bool>::Set(lua_State* L, const bool& value) {
        lua_pushboolean(L, (int)value);
    }

    template<>
    static void LuaParameter<int&>::Set(lua_State* L, const int& value) {
        lua_pushnumber(L, (lua_Number)value);
    }
    template<>
    static void LuaParameter<float&>::Set(lua_State* L, const float& value) {
        lua_pushnumber(L, (lua_Number)value);
    }
    template<>
    static void LuaParameter<double&>::Set(lua_State* L, const double& value) {
        lua_pushnumber(L, (lua_Number)value);
    }
    template<>
    static void LuaParameter<uint32&>::Set(lua_State* L, const uint32& value) {
        lua_pushnumber(L, (lua_Number)value);
    }
    template<>
    static void LuaParameter<bool&>::Set(lua_State* L, const bool& value) {
        lua_pushboolean(L, (int)value);
    }

    template<typename ... Args>
    struct LuaParameterPack {
        static std::tuple_element_t<0, std::tuple<Args...>> Get(lua_State* L, int idx) {
            using Arg = std::tuple_element_t<0, std::tuple<Args...>>;
            return LuaParameter<Arg>::Get(L, idx);
        }
    };

}