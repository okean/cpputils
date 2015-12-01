#pragma once

#include <vector>
#include <memory>

namespace Util {

class SplitedString
{
public:
    SplitedString(
        const std::string &str,
        const char * separator,
        bool trim = true,
        bool skipEmpty = true);
    ~SplitedString();

public: // public typedefs
    typedef std::string                 Token;
    typedef std::vector<Token>          Tokens;
    typedef Tokens::iterator            Iterator;

public: // interface
    Iterator    begin() const;
    Iterator    end()   const;
    size_t      count() const;

private: // internal typedefs
    typedef std::shared_ptr<Tokens>     TokensPtr;

private: // internal static helpers
    static TokensPtr split(
        const std::string &str,
        const char * separator,
        bool trim,
        bool skipEmpty);

private: // member variables
    TokensPtr _tokens;
};

} // namespace Util
