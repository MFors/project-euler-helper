/*
    Project Euler Helper v0.0.2
    Mikael Fors 2014

    type:     number
    function: various
    desc:     several integral functions
*/
#include "number.h"
#include <cmath>
#include <random>
#include <boost/dynamic_bitset.hpp>

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
    bool isPandigital(int p_n) {
        int k = 1023, t = 0, r = 0;
        while(p_n > 0) {
            t = 1 << (p_n % 10);
            k ^= t;
            if(!(k & ~t) || !(k & 1))
                return false;
            p_n /= 10;
            ++r;
        }
        return (k & ((1 << (r + 1)) - 1)) == 1;
    }
    
    template<typename T, EnableIf<std::is_integral<T>> ... >
    bool isTriangleNumber(T p_n) {
        T m = (p_n << 3) + 1;
        double d = std::sqrt(m);
        return (T)d == d && (m & 1);
    }

    template<typename T, EnableIf<std::is_integral<T>> ... >
    bool isPentagonalNumber(T p_n) {
        double m = std::sqrt(24 * p_n + 1);
        p_n = (T)m;
        return p_n == m && (p_n % 6 == 5);
    }

    template<typename T, EnableIf<std::is_integral<T>> ... >
    bool isHexagonalNumber(T p_n) {
        double m = (std::sqrt((p_n << 3) + 1) + 1) / 4;
        return (T)m == m;
    }
    
    template<typename T, EnableIf<std::is_integral<T>> ... >
    std::vector<T> allPrimesUpTo(T p_n) {
        // Eliminate trivial cases
        if(p_n < 2)
            return std::vector<T>{};
        if(p_n < 3)
            return std::vector<T>{2};
        if(p_n < 5)
            return std::vector<T>{2, 3};

        T size = (p_n / 6),
          difference = (p_n - 6 * size),
          offset,
          ptr,
          position,
          value,
          jump[2];

        T counter = 2;

        size = (size << 1) - (!difference ? 1 : 0) + (difference == 5 ? 1 : 0);

        // Bit Sieve where 0 (default) <=> prime and 1 <=> composite
        boost::dynamic_bitset<> sieve(size);

        T sSize = (T)sieve.size(); // conversion cached for while-loop

        for(auto i = 0; i < sieve.size(); ++i) {
            if(sieve[i])
                continue;
            ++counter;
            offset = (i >> 1) + 1;
            value = 6 * offset + ((i & 1) ? 1 : -1);
            offset <<= 1;
            jump[0] = value + offset;
            jump[1] = value - offset;
            ptr = 0;
            position = i;

            while(position + jump[ptr] < sSize) {
                position += jump[ptr];
                sieve[position] = 1;
                ptr ^= 1;
            }
        }

        T* primes = new T[counter];
        primes[0] = 2;
        primes[1] = 3;

        T pos = 2;

        for(boost::dynamic_bitset<>::size_type i = 0; i < sieve.size(); ++i) {
            if(!sieve[i]) {
                primes[pos] = 6 * ((i >> 1) + 1) + (i & 1 ? 1 : - 1);
                ++pos;
            }
        }

        std::vector<T> result(primes, primes + counter);
        delete[] primes;

        return result;
    }
    
    template<typename T, EnableIf<std::is_integral<T>> ... >
    std::vector<T> factorizationOf(T p_n) {
        std::vector<T> primes = allPrimesUpTo((T)std::sqrt(p_n)), result;
        for(typename std::vector<T>::iterator prime = primes.begin(); prime != primes.end(); ++prime) {
            while(!(p_n % *prime)) {
                p_n /= *prime;
                result.push_back(*prime);
            }
        }
        if(p_n != 1)
            result.push_back(p_n);
        return result;
    }    
    
    template<typename T, EnableIf<std::is_integral<T>> ... >
    T powMod(T p_base, T p_power, T p_mod) {
        T result = 1;
        while(p_power > 0) {
            if(p_power & 1) {
                result *= p_base;
                result %= p_mod;
            }
            p_base *= p_base;
            p_base %= p_mod;
            p_power >>= 1;
        }
        return result;
    }

    template<typename T, EnableIf<std::is_integral<T>> ... >
    bool rabinMiller(T p_n, int p_k) {

        if(p_n < 2)
            return false;
        if(p_n != 2 && !(p_n & 1))
            return false;

        T s = 0, d = p_n - 1, x, a;
        bool doWitnessLoop;
        std::random_device randDev;
        std::mt19937 generator(randDev());
        std::uniform_int_distribution<T> distr(1, p_n - 1);

        while(!(d % 2)) {
            ++s;
            d >>= 1;
        }

        for(int i = 0; i < p_k; ++i) {
            doWitnessLoop = false;

            a = distr(generator);
            x = powMod(a, d, p_n);
            if(x == 1 || x == p_n - 1)
                continue;
            for(T j = 0; j < s - 1; ++j) {
                x = powMod(x, 2, p_n);
                if(x == 1) {
                    return false;
                } else if(x == p_n - 1) {
                    doWitnessLoop = true;
                    break;
                }
            }
            if(!doWitnessLoop)
                return false;
        }
        return true;
    }
}
}
