#pragma once
#include "core.h"

namespace spr {

    class Console {
    public:
        static void Init();

        template<typename Arg, typename ... Args>
        static void WriteLn(const std::string& separator, const std::string& color, Arg&& arg, Args&& ... args) {
            std::cout << color << std::forward<Arg>(arg);
            ((std::cout << separator << std::forward<Args>(args)), ...);
            std::cout << std::endl;
        }

        template<typename Arg, typename ... Args>
        static void Log(Arg&& arg, Args&& ... args) {
            WriteLn(" ", "\u001b[0m", arg, args...);
        }

        template<typename Arg, typename ... Args>
        static void LogError(Arg&& arg, Args&& ... args) {
            WriteLn(" ", "\u001b[31m", arg, args...);
        }

        template<typename Arg, typename ... Args>
        static void LogWarning(Arg&& arg, Args&& ... args) {
            WriteLn(" ", "\u001b[33m", arg, args...);
        }

        template<typename Arg, typename ... Args>
        static void LogInfo(Arg&& arg, Args&& ... args) {
            WriteLn(" ", "\u001b[32m", arg, args...);
        }
    };

}