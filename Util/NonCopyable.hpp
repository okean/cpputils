#pragma once

namespace Util {

class NonCopyable
{
public:
    NonCopyable() = default;
private:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

} // namespace Util
