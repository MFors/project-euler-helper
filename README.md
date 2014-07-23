Project-Euler-Helper
====================
The aim of this project is to create a nice Python module using boost.python and C++ for performance-critical functions and structures used in conjunction with Project Euler solutions. It will also double as a C++ library for the same purpose. Basically a **good-to-have** library of goodness.

Build using *-std=c++11*.

#### Number
Contains several useful integral functions, most are templated for integral input (return will always match input type if valid).

| Name | Arguments | Returns |
| :---- | :---: | :--- |
|isDecimalPalindrome | T (std::is_integral) | bool |
|isBinaryPalindrome | T (std::is_integral) | bool |
|digitalSum | T (std::is_integral) | T |
|binarySum | T (std::is_integral) | T |
|isPandigital | int n, int length | bool |

```c++
// Default init (empty)
bool b;
b = project_euler_helper::number::isDecimalPalindrome(25);      // false
b = project_euler_helper::number::isDecimalPalindrome(252);     // true
b = project_euler_helper::number::isDecimalPalindrome(561165L); // true

b = project_euler_helper::number::isBinaryPalindrome(25);           // false
b = project_euler_helper::number::isDecimalPalindrome(6870778675L); // true

int n = project_euler_helper::number::digitalSum(1048);   // 13
long m = project_euler_helper::number::digitalSum(1048L); // 13L

n = project_euler_helper::number::binarySum(1048); // 3

b = project_euler_helper::number::isPandigital(123, 3);       // true
b = project_euler_helper::number::isPandigital(1233, 4);      // false
b = project_euler_helper::number::isPandigital(987654321, 9); // true
```


#### Trees: Trie
Currently supports *insert*, *contains*, *containsPrefix* and *contentWithPrefix*. **contains(const std::string&)** returns true if the argument has been inserted into the trie while **containsPrefix(const std::string&)** returns true if the argument is a prefix of any inserted string. By definition any string is a prefix of itself. Finally, **contentWithPrefix(const std::string&)** returns a *std::vector&lt;std::string&gt;* of all strings in the trie with the argument prefix. 

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
```
