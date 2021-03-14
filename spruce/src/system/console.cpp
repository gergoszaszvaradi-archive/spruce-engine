#include "sprpch.h"
#include "console.h"

namespace spr {

    void Console::Init()
    {
        // WINDOWS 10 only!
        SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }

}
