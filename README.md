Project-Euler-Helper
====================
The aim of this project is to create a nice Python module using boost.python and C++ for performance-critical functions and structures used in conjunction with Project Euler solutions. It will also double as a C++ library for the same purpose. Basically a **good-to-have** library of goodness.

Build using *-std=c++11*.

#### Number
Contains several useful integral functions, most are templated for integral input (return will always match input type if valid). Note that *pandigital* is defined in the project euler way, i.e. a number n such that the digits 1..len(n) < 10 are present exactly once.

| Name | Arguments | Returns |
| :---- | :---: | :--- |
|isDecimalPalindrome | T (std::is_integral) | bool |
|isBinaryPalindrome | T (std::is_integral) | bool |
|digitalSum | T (std::is_integral) | T |
|binarySum | T (std::is_integral) | T |
|isPandigital | int n, int length | bool |
|isTriangleNumber | T (std::is_integral) | bool |
|isPentagonalNumber | T (std::is_integral) | bool |
|isHexagonalNumber | T (std::is_integral) | bool |
|powMod | T, T, T | T |
|rabinMiller | T, int | bool |

```c++
// Example use
bool b;
b = project_euler_helper::number::isDecimalPalindrome(25);      // false
b = project_euler_helper::number::isDecimalPalindrome(252);     // true
b = project_euler_helper::number::isDecimalPalindrome(561165L); // true

b = project_euler_helper::number::isBinaryPalindrome(25);           // false
b = project_euler_helper::number::isBinaryPalindrome(6870778675L);  // true

int n = project_euler_helper::number::digitalSum(1048);   // 13
long m = project_euler_helper::number::digitalSum(1048L); // 13L

n = project_euler_helper::number::binarySum(1048); // 3

b = project_euler_helper::number::isPandigital(123, 3);       // true
b = project_euler_helper::number::isPandigital(1233, 4);      // false
b = project_euler_helper::number::isPandigital(987654321, 9); // true

b = project_euler_helper::number::isTriangleNumber(7);           // false
b = project_euler_helper::number::isTriangleNumber(1533776805L); // true

b = project_euler_helper::number::isPentagonalNumber(35); // true
b = project_euler_helper::number::isHexagonalNumber(15);  // true

int result = project_euler_helper::number::powMod(2, 3, 3); // 2^3 mod 3 = 8 mod 3 = 2

b = rabinMiller(2013, 2); // false
```


#### Trees: Trie

| Name | Arguments | Returns |
| :---- | :---: | :--- |
| insert | std::string | void |
| insert | std::initializer_list&lt;std::string&gt; | void |
| contains | std::string | bool |
| containsPrefix | std::string | bool |
| contentWithPrefix | std::string | std::vector&lt;std::string&gt; |


**contains** returns true if the argument has been inserted into the trie while **containsPrefix** returns true if the argument is a prefix of any inserted string. By definition any string is a prefix of itself. Finally, **contentWithPrefix** returns a *std::vector&lt;std::string&gt;* of all strings in the trie with the argument prefix. 

Example use below.

```c++
// Default init (empty)
project_euler_helper::Trie myPrefixTree;
myPrefixTree.insert("johnny");

bool b = myPrefixTree.contains("john");   // False
b = myPrefixTree.contains("johnny");      // True
b = myPrefixTree.containsPrefix("john");  // True
b = myPrefixTree.containsPrefix("johnny") // True

myPrefixTree.insert("jay");
myPrefixTree.insert("johan");

std::vector<std::string> v = myPrefixTree.contentWithPrefix("j"); // {"johnny", "jay", "johan"}
v = myPrefixTree.contentWithPrefix("jo");                         // {"johnny", "johan"}

// Build init (build from vector of strings)
std::vector<std::string> strings{"one", "squid", "pluto"};
project_euler_helper::Trie myOtherPrefixTree{strings};

// Build and insert std::initializer_list
project_euler_helper::Trie myThirdPrefixTree{"a", "b," "c"};
myThirdPrefixTree.insert({"d", "e", "f"});

// Assignment works as expected
myOtherPrefixTree = myThirdPrefixTree;
myOtherPrefixTree.contains("squid"); // false
myOtherPrefixTree.contains("d");     // true
```
