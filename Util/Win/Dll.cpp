#include "stdafx.h"
#include "Dll.h"
#include <Util/Text.h>
#include <Windows.h>

using namespace Util;
using namespace Util::Win;

Dll::Dll(const std::string &path)
    : _module{ loadLibrary(Text::Convert::wcsFromUtf(path)) }
{
    if (!_module)
    {
        throw std::exception(("Failed to load module: " + path).c_str());
    }
}

Dll::~Dll()
{
    ::FreeLibrary(_module);
}

// interface

Dll::operator Module () const
{
    return _module;
}

// internal class helpers

Dll::Module Dll::loadLibrary(const std::wstring &path)
{
    wchar_t curDllDir[MAX_PATH];
    bool updateDllDir = false;
 
    size_t pos = path.size();

    while (pos-- && path[pos] != L'\\' && path[pos] != L'/');

    if (pos != std::wstring::npos)
    {
        ::GetDllDirectory(_countof(curDllDir), curDllDir);
        
        ::SetDllDirectory(path.substr(0, pos).data());

        updateDllDir = true;
    }

    Module module = ::LoadLibrary(path.data());

    if (updateDllDir)
    {
        ::SetDllDirectory(curDllDir);
    }

    return module;
}
