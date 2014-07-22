Project-Euler-Helper
====================
The aim of this project is to create a nice Python module using boost.python and C++ for performance-critical functions and structures used in conjunction with Project Euler solutions. It will also double as a C++ library for the same purpose. Basically a **good-to-have** library of goodness.

Build using *-std=c++11*.


##Feature Outline
| Type | Function | Status |
| :------- | :---- | :----:|
| Prime | Sieve | :white_check_mark: |
| Prime | Factorization | Next Push |
| Prime | Miller-Rabin | |
| Divisor | Proper Divisors | Next Push |
| Divisor | Totient Function | Next Push |
| Combinatorics | ... | ... |
| Trees | BST | |
| Trees | R/B | |
| Trees | Trie | :white_check_mark: |
| Numbers | Triangle Generator | Next Push |
| Numbers | Mod Chain Multiply |  |


#### Trees: Trie
Currently supports add, contains, containsPrefix. *contains* returns true if the argument has been inserted into the trie, *containsPrefix* returns true if the argument is a substring of any inserted string. By definition any string is a substring of itself. Example use below.

```c++
// Default init (empty)
project_euler_helper::Trie myPrefixTree;
myPrefixTree.add("johnny");
bool b = myPrefixTree.contains("john");   // False
b = myPrefixTree.contains("johnny");      // True
b = myPrefixTree.containsPrefix("john");  // True
b = myPrefixTree.containsPrefix("johnny") // True

// Build init (build from vector of strings)
std::vector<std::string> strings{"one", "squid", "pluto"};
project_euler_helper::Trie myOtherPrefixTree{strings};
```
