/*
    Project Euler Helper v0.0.2
    Mikael Fors 2014

    type:     number
    function: various
    desc:     several integral functions
*/
#include <type_traits>
#include <vector>

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

    bool isPandigital(int n);
    
    template<typename T, EnableIf<std::is_integral<T>> ... >
    T powMod(T p_base, T p_power, T p_mod);

    template<typename T, EnableIf<std::is_integral<T>> ... >
    bool rabinMiller(T p_n, int p_k);    
    
    template<typename T, EnableIf<std::is_integral<T>> ... >
    bool isTriangleNumber(T p_n);
    
    template<typename T, EnableIf<std::is_integral<T>> ... >
    bool isPentagonalNumber(T p_n);

    template<typename T, EnableIf<std::is_integral<T>> ... >
    bool isHexagonalNumber(T p_n);
    
    template<typename T, EnableIf<std::is_integral<T>> ... >
    std::vector<T> allPrimesUpTo(T p_n);
    
    template<typename T, EnableIf<std::is_integral<T>> ... >
    std::vector<T> factorizationOf(T p_n);
    
}
}
