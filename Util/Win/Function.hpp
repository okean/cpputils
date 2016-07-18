#pragma once

#include "Dll.h"
#include <Windows.h>
#include <string>

namespace Util {
namespace Win {

template <typename T>
class Function
{
public:
    Function(const Dll &dll, const std::string &name)
        : _func{ getProcAddress(dll, name) }
    {
        if (!_func)
        {
            throw std::exception(("Failed to retrieve function address: " + name).c_str());
        }
    }

    virtual ~Function()
    {
    }

public: // interface
    operator T * () const
    {
        return _func;
    }

private: // internal class helpers
    static T * getProcAddress(const Dll &dll, const std::string &name)
    {
        return reinterpret_cast<T *>(::GetProcAddress(dll, name.c_str()));
    }

private: // member variables
    T * _func;
};

} // namespace Win
} // namespace Util
