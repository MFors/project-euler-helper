/*

    Project Euler Helper v0.0.1
    Mikael Fors 2014

    function: generatePrimesUpTo
    desc:     a memory efficient prime sieve

*/

#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
using namespace std;

vector<int> generatePrimesUpTo(int n) {
    vector<int> primes;

    if(n < 2)
        return primes;
    primes.push_back(2);
    if(n < 3)
        return primes;
    primes.push_back(3);
    if(n < 5)
        return primes;

    int size, difference, offset, ptr, position, value, jump[2];

    size = (n / 6);
    difference = n - 6 * size;
    size = 2 * size - (!difference ? 1 : 0) + (difference == 5 ? 1 : 0);

    boost::dynamic_bitset<> sieve(size);

    for(boost::dynamic_bitset<>::size_type i = 0; i < sieve.size(); ++i) {
        if(sieve[i])
            continue;
        
        offset = (i >> 1) + 1;
        value = 6 * offset + ((i & 1) ? 1 : -1);
        jump[0] = value + 2 * offset;
        jump[1] = value - 2 * offset;
        ptr = 0;
        position = i;
        
        while(uint(position + jump[ptr]) < sieve.size()) {
            position += jump[ptr];
            sieve[position] = 1;
            ptr ^= 1;
        }

    }

    for(boost::dynamic_bitset<>::size_type i = 0; i < sieve.size(); ++i) {
        if(!sieve[i]) {
            primes.push_back(6 * ((i >> 1) + 1) + (i & 1 ? 1 : -1));
        }
    }

    return primes;
}
