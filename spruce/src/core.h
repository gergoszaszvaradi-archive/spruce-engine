#pragma once
#include <cstdint>
#include "system/console.h"

#ifdef SPR_BUILD_DLL
#ifdef SPR_DLL
#define SPR_API __declspec(dllexport)
#else
#define SPR_API __declspec(dllimport)
#endif
#else
#define SPR_API
#endif

#undef min
#undef max

#define BITFLAG(x) 1 << x
#ifdef SPR_DEBUG
#define ASSERT(expr, ...) {if(!(expr)){spr::Console::LogError("Assertion at", __FILE__, ":", __LINE__, "\n", __VA_ARGS__);__debugbreak();}}
#else
#define ASSERT(expr, ...) {if(expr){}}
#endif

#define REGISTER_TYPE_NAME(type) static const std::string& GetTypeName() { return #type; }

namespace spr {
    typedef unsigned char uchar;
    typedef wchar_t wchar;
    typedef int32_t int32;
    typedef int64_t int64;
    typedef uint32_t uint32;
    typedef uint64_t uint64;

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    Ref<T> CreateRef(Args&& ... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
    template<typename T>
    Ref<T> CreateNullRef() {
        return Ref<T>(nullptr);
    }
    template<typename T>
    Ref<T> ToRef(T* ptr) {
        return Ref<T>(ptr);
    }

    template<typename T>
    static std::string ToString(const T& t) {
        return std::to_string(t);
    }
}