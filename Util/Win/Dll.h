#pragma once

#include <string>

struct HINSTANCE__;

namespace Util {
namespace Win {

class Dll
{
public:
    Dll(const std::string &path);
    virtual ~Dll();

public: // public typedefs
    typedef HINSTANCE__ *Module;

public: // interface
    operator Module () const;

private: // internal class helpers
    static Module loadLibrary(const std::wstring &path);

private: // member variables
    Module _module;
};

} // namespace Win
} // namespace Util
