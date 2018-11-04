#include "catch.hpp"

class HexadecimalDigit : public Catch::MatcherBase<char>
{
  public:
    HexadecimalDigit() {}
    virtual bool match(char const& c) const override;
    virtual std::string describe() const;
};

inline HexadecimalDigit IsHexadecimalDigit()
{
    return HexadecimalDigit();
}
