/*
    Project Euler Helper v0.0.2
    Mikael Fors 2014

    type:     number
    function: various
    desc:     several integral functions
*/
#include "number.h"

namespace project_euler_helper {
namespace number {

    template <typename Condition>
    using EnableIf = typename std::enable_if<Condition::value>::type;

    template<typename T, EnableIf<std::is_integral<T>> ... >
    bool isDecimalPalindrome(T n) {
        T m = n, k = 0;
        while(m > 0) {
            k *= 10;
            k += m % 10;
            m /= 10;
        }
        return k == n;
    }

    template<typename T, EnableIf<std::is_integral<T>> ... >
    bool isBinaryPalindrome(T n) {
        T m = n, k = 0;
        while(m > 0) {
            k <<= 1;
            k |= m & 1;
            m >>= 1;
        }
        return k == n;
    }


    template<typename T, EnableIf<std::is_integral<T>> ... >
    T digitalSum(T n) {
        T m = n, k = 0;
        while(m > 0) {
            k += m % 10;
            m /= 10;
        }
        return k;
    }

    template<typename T, EnableIf<std::is_integral<T>> ... >
    T binarySum(T n) {
        T k = 0;
        while(n > 0) {
            n &= (n - 1);
            ++k;
        }
        return k;
    }

    // def: n is pandigital <=> 1..length<10 each occur once
    bool isPandigital(int n, int length) {
        int k = 1023, t = 0;
        while(n > 0) {
            t = 1 << (n % 10);
            k ^= t;
            if(!(k & ~t) || !(k & 1))
                return false;
            n /= 10;
        }
        return (k & ((1 << (length + 1)) - 1)) == 1;
    }
    
    template<typename T, EnableIf<std::is_integral<T>> ... >
    bool isTriangleNumber(T n) {
        T m = (n << 3) + 1;
        double d = std::sqrt(m);
        return (T)d == d && (m & 1);
    }
}
}
