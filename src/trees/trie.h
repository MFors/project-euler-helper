/*

    Project Euler Helper v0.0.2
    Mikael Fors 2014

    type:     trees
    function: trie
    desc:     prefix tree for strings

*/
#include <map>
#include <vector>
#include <string>

namespace project_euler_helper {

    struct PrefixSearchResult {
        bool found;
        bool isLeaf;
    };

    class TrieNode {
        std::map<char, TrieNode*> m_children;
        int m_count;
    public:
        TrieNode() {};
        TrieNode(const char* p_string);
        ~TrieNode();

        void add(const char* p_string);

        PrefixSearchResult find(const char* p_string);
    };

    class Trie {
        TrieNode* m_root;
    public:
        Trie() : m_root{new TrieNode} {};
        Trie(const std::vector<std::string>& p_strings);
        ~Trie();

        void add(const std::string& p_string);

        bool contains(const std::string& p_string);
        bool containsPrefix(const std::string& p_prefix);
    };
}