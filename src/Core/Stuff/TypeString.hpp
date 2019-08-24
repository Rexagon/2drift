#pragma once

namespace core
{
namespace details
{
template <char... Chars>
struct str
{
    static constexpr const char data[sizeof...(Chars) + 1] = {Chars..., '\0'};
    static constexpr int size = sizeof...(Chars);
};

}  // namespace details

// ALERT!
// GCC SPECIFIC HORRIBLE (NO) STUFF BEGINS

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
template <typename CharT, CharT... String>
constexpr details::str<String...> operator"" _t()
{
    return details::str<String...>();
}
#pragma GCC diagnostic pop
// GCC SPECIFIC HORRIBLE (NO) STUFF ENDS
// P.S. waiting for C++20

#define typestring(x) decltype(x##_t)

}  // namespace core
