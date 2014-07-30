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
#include <initializer_list>

namespace project_euler_helper {

    struct PrefixSearchResult {
        bool found;
        bool isLeaf;
    };

    class TrieNode {
        std::map<char, TrieNode*> m_children;
        int m_count;
    public:
        TrieNode():m_count{0} {};
        TrieNode(const char* p_string);
        ~TrieNode();

        void insert(const char* p_string);
        PrefixSearchResult find(const char* p_string);
        std::vector<std::string> contentWithPrefix(const char* p_prefix);
    };

    class Trie {
        TrieNode* m_root;
    public:
        Trie() : m_root{new TrieNode} {};
        Trie(const std::vector<std::string>& p_strings);
        Trie(const std::initializer_list<std::string>& p_list);
        ~Trie();

        Trie(const Trie& p_trie);
        Trie& operator=(const Trie& p_trie);

        Trie(Trie&& p_trie);
        Trie& operator=(Trie&& p_trie);

        void insert(const std::string& p_string);
        void insert(const std::initializer_list<std::string>& p_list);

        bool contains(const std::string& p_string) const;
        bool containsPrefix(const std::string& p_prefix) const;
        std::vector<std::string> contentWithPrefix(const std::string& p_prefix) const;
    };

    struct PrefixQueueItem {
        TrieNode* node;
        std::string key;
    };
}
