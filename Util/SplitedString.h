#pragma once

#include <vector>
#include <memory>

namespace Util {

class SplitedString
{
public:
    SplitedString(
        const std::string &str,
        char sep,
        bool trim = true,
        bool skipEmpty = true);
    SplitedString(
        const std::string &str,
        const char * sep,
        bool trim = true,
        bool skipEmpty = true);
    ~SplitedString();

public: // public typedefs
    typedef std::string                 Token;
    typedef std::vector<Token>          Tokens;
    typedef Tokens::iterator            Iterator;

public: // interface
    Iterator        begin() const;
    Iterator        end()   const;
    size_t          count() const;
    std::string &   at(size_t pos) const;

    std::string &   operator[](size_t pos) const;

private: // internal typedefs
    typedef std::shared_ptr<Tokens>     TokensPtr;

private: // internal static helpers
    template <typename Separator>
    static TokensPtr split(
        const std::string &str,
        Separator s,
        size_t len,
        bool trim,
        bool skipEmpty);

private: // member variables
    TokensPtr _tokens;
};

} // namespace Util
