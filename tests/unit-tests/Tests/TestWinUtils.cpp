#include "stdafx.h"
#include <Util/Text.h>
#include <Util/Win/Dll.h>
#include <Util/Win/Function.hpp>
#include <Windows.h>

using namespace Util;
using namespace Util::Win;

TEST(Dll, Sanity)
{
    wchar_t winDir[MAX_PATH];

    ::GetWindowsDirectory(winDir, _countof(winDir));

    std::string libPath = Text::Convert::utfFromWcs(winDir).append("\\System32\\User32.dll");

    ASSERT_NO_THROW(
        Dll dll(libPath);
    );
}

TEST(Function, Sanity)
{
    Dll dll("User32.dll");
    ASSERT_NE(nullptr, dll);
    
    Function<HWND(void)> getShellWindow(dll, "GetShellWindow");
    ASSERT_NE(nullptr, getShellWindow);
}
