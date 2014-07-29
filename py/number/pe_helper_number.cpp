/*
    Project Euler Helper v0.0.2A
    PYTHON MODULE VERSION
    Mikael Fors 2014

    type:     number
    function: various
    desc:     several integral functions

    TODO: Complete export to py
*/

#include <boost/python.hpp>
#include <boost/dynamic_bitset.hpp>

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

BOOST_PYTHON_MODULE(pe_helper_number) {
    boost::python::def("allPrimesUpTo", allPrimesUpTo);
}
