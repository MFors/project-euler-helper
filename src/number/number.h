/*
    Project Euler Helper v0.0.2
    Mikael Fors 2014

    type:     number
    function: various
    desc:     several integral functions
*/
#include <type_traits>

namespace project_euler_helper {
namespace number {

    template <typename Condition>
    using EnableIf = typename std::enable_if<Condition::value>::type;

    template<typename T, EnableIf<std::is_integral<T>> ... >
    bool isDecimalPalindrome(T n);

    template<typename T, EnableIf<std::is_integral<T>> ... >
    bool isBinaryPalindrome(T n);

    template<typename T, EnableIf<std::is_integral<T>> ... >
    T digitalSum(T n);

    template<typename T, EnableIf<std::is_integral<T>> ... >
    T binarySum(T n);

    bool isPandigital(int n, int length);
}
}
