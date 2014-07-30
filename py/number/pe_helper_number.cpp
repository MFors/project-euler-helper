/*
    Project Euler Helper v0.1
    PYTHON MODULE VERSION
    Mikael Fors 2014

    type:     number
    function: various
    desc:     several integral functions

    TODO: divisorsOf, properDivisorsOf, totient
    XXX:  eliminate _ internal C++ calls
*/
#include <boost/python.hpp>
#include <boost/dynamic_bitset.hpp>
#include <cmath>
#include <vector>
#include <random>

template<typename T>
inline T pyObjToType(const boost::python::object& p_pyObj) {
    return boost::python::extract<T>(p_pyObj);
}

boost::python::object isDecimalPalindrome(boost::python::object p_pyObj) {
    long n = pyObjToType<long>(p_pyObj);
    long m = n, k = 0;
    while(m > 0) {
        k *= 10;
        k += m % 10;
        m /= 10;
    }
    return boost::python::object(k == n);
}

boost::python::object isBinaryPalindrome(boost::python::object p_pyObj) {
    long n = pyObjToType<long>(p_pyObj);
    long m = n, k = 0;
    while(m > 0) {
        k <<= 1;
        k |= m & 1;
        m >>= 1;
    }
    return boost::python::object(k == n);
}

boost::python::object digitalSum(boost::python::object p_pyObj) {
    long n = pyObjToType<long>(p_pyObj), k = 0;
    while(n > 0) {
        k += n % 10;
        n /= 10;
    }
    return boost::python::object(k);
}

boost::python::object binarySum(boost::python::object p_pyObj) {
    long n = pyObjToType<long>(p_pyObj), k = 0;
    while(n > 0) {
        n &= (n - 1);
        ++k;
    }
    return boost::python::object(k);
}

template<typename T>
std::vector<T> _allPrimesUpTo(T p_n) {
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

boost::python::list factorizationOf(boost::python::object p_pyObj) {
    long n = pyObjToType<long>(p_pyObj);
    std::vector<long> primes = _allPrimesUpTo((long)std::sqrt(n));
    boost::python::list result;
    for(auto prime = primes.begin(); prime != primes.end(); ++prime) {
        while(!(n % *prime)) {
            n /= *prime;
            result.append(*prime);
        }
    }
    if(n != 1)
        result.append(n);
    return result;
}


boost::python::object isPandigital(boost::python::object p_pyObj) {
    int n = pyObjToType<int>(p_pyObj), k = 1023, t = 0, r = 0;
    while(n > 0) {
        t = 1 << (n % 10);
        k ^= t;
        if(!(k & ~t) || !(k & 1))
            return boost::python::object(false);
        n /= 10;
        ++r;
    }
    return boost::python::object((k & ((1 << (r + 1)) - 1)) == 1);
}

boost::python::object isTriangleNumber(boost::python::object p_pyObj) {
    long m = (pyObjToType<long>(p_pyObj) << 3) + 1;
    double d = std::sqrt(m);
    return boost::python::object((long)d == d && (m & 1));
}

boost::python::object isPentagonalNumber(boost::python::object p_pyObj) {
    double m = std::sqrt(24 * pyObjToType<long>(p_pyObj) + 1);
    long n = (long)m;
    return boost::python::object(n == m && (n % 6 == 5));
}

boost::python::object isHexagonalNumber(boost::python::object p_pyObj) {
    double m = (std::sqrt((pyObjToType<long>(p_pyObj) << 3) + 1) + 1) / 4;
    return boost::python::object((long)m == m);
}


boost::python::list allPrimesUpTo(boost::python::object p_pyObj) {

    namespace py = boost::python;
    long p_n = py::extract<long>(p_pyObj);
    py::list primes;

    // Eliminate trivial cases
    if(p_n < 2)
        return primes;
    primes.append(2);
    if(p_n < 3)
        return primes;
    primes.append(3);
    if(p_n < 5)
        return primes;

    long size = (p_n / 6),
         difference = (p_n - 6 * size),
         offset,
         ptr,
         position,
         value,
         jump[2];

    long counter = 2;

    size = (size << 1) - (!difference ? 1 : 0) + (difference == 5 ? 1 : 0);

    // Bit Sieve where 0 (default) <=> prime and 1 <=> composite
    boost::dynamic_bitset<> sieve(size);

    long sSize = (long)sieve.size(); // conversion cached for while-loop

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

    long pos = 2;

    for(boost::dynamic_bitset<>::size_type i = 0; i < sieve.size(); ++i) {
        if(!sieve[i]) {
            primes.append(6L * ((i >> 1) + 1) + (i & 1 ? 1 : - 1));
            ++pos;
        }
    }

    return primes;
}


long _powMod(long p_base, long p_power, long p_mod) {
    long result = 1;
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

boost::python::object powMod(boost::python::object p_pyObjB,
    boost::python::object p_pyObjP,
    boost::python::object p_pyObjM) {

    long p_base = pyObjToType<long>(p_pyObjB),
         p_power = pyObjToType<long>(p_pyObjP),
         p_mod = pyObjToType<long>(p_pyObjM);

    long result = 1;
    while(p_power > 0) {
        if(p_power & 1) {
            result *= p_base;
            result %= p_mod;
        }
        p_base *= p_base;
        p_base %= p_mod;
        p_power >>= 1;
    }
    return boost::python::object(result);
}

boost::python::object rabinMiller(boost::python::object p_pyObjN,
    boost::python::object p_pyObjK) {

    long p_n = pyObjToType<long>(p_pyObjN), p_k = pyObjToType<long>(p_pyObjK);

    if(p_n < 2)
        return boost::python::object(false);
    if(p_n != 2 && !(p_n & 1))
        return boost::python::object(false);

    long s = 0, d = p_n - 1, x, a;
    bool doWitnessLoop;
    std::random_device randDev;
    std::mt19937 generator(randDev());
    std::uniform_int_distribution<long> distr(1, p_n - 1);


    while(!(d % 2)) {
        ++s;
        d >>= 1;
    }

    for(int i = 0; i < p_k; ++i) {
        doWitnessLoop = false;

        a = distr(generator);
        x = _powMod(a, d, p_n);
        if(x == 1 || x == p_n - 1)
            continue;
        for(long j = 0; j < s - 1; ++j) {
            x = _powMod(x, 2, p_n);
            if(x == 1) {
                return boost::python::object(false);
            } else if(x == p_n - 1) {
                doWitnessLoop = true;
                break;
            }
        }
        if(!doWitnessLoop)
            return boost::python::object(false);
    }
    return boost::python::object(true);
}

BOOST_PYTHON_MODULE(pe_helper_number) {
    boost::python::def("isDecimalPalindrome", isDecimalPalindrome);
    boost::python::def("isBinaryPalindrome", isBinaryPalindrome);
    boost::python::def("allPrimesUpTo", allPrimesUpTo);
    boost::python::def("digitalSum", digitalSum);
    boost::python::def("binarySum", binarySum);
    boost::python::def("factorizationOf", factorizationOf);
    boost::python::def("isPandigital", isPandigital);
    boost::python::def("isTriangleNumber", isTriangleNumber);
    boost::python::def("isPentagonalNumber", isPentagonalNumber);
    boost::python::def("isHexagonalNumber", isHexagonalNumber);
    boost::python::def("powMod", powMod);
    boost::python::def("rabinMiller", rabinMiller);
}
