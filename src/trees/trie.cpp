/*

    Project Euler Helper v0.0.2
    Mikael Fors 2014

    type:     trees
    function: trie
    desc:     prefix tree for strings

*/

#include "trie.h"

namespace project_euler_helper {

    /* ######## ------- NODE ------- ######## */

    TrieNode::TrieNode(const char* p_string) {
        if(*p_string != 0) {
            m_children[*p_string] = new TrieNode(p_string + 1);
        }
    }

    TrieNode::~TrieNode() {
        for(std::map<char, TrieNode*>::iterator i = m_children.begin();
            i != m_children.end(); ++i) {
            delete i->second;
        }
    };

    void TrieNode::add(const char* p_string) {
        if(*p_string != 0) {
            if(m_children.find(*p_string) != m_children.end()) {
                m_children[*p_string]->add(p_string + 1);
            } else {
                m_children[*p_string] = new TrieNode;
                m_children[*p_string]->add(p_string + 1);
            }
        } else {
            m_count++;
        }
    }

    PrefixSearchResult TrieNode::find(const char* p_string) {
        if(*p_string != 0) {
            if(m_children.find(*p_string) != m_children.end()) {
                return m_children[*p_string]->find(p_string + 1);
            } else {
                return (PrefixSearchResult){ 0, 0 };
            }
        } else {
            return (PrefixSearchResult){ 1, m_count > 0 };
        }
    }


    /* ######## ------- TREE ------- ######## */

    Trie::Trie(const std::vector<std::string>& p_strings) {
        if(p_strings.size()) {
            m_root = new TrieNode(p_strings[0].c_str());
            for(uint i = 1; i < p_strings.size(); ++i) {
                m_root->add(p_strings[i].c_str());
            }
        } else {
            m_root = new TrieNode;
        }
    }

    Trie::~Trie() {
        delete m_root;
    }

    void Trie::add(const std::string& p_string) {
        if(p_string.length())
            m_root->add(p_string.c_str());
    }

    bool Trie::contains(const std::string& p_string) {
        return p_string.length() ? m_root-> find(p_string.c_str()).isLeaf : 0;

    }

    bool Trie::containsPrefix(const std::string& p_prefix) {
        return p_prefix.length() ? m_root -> find(p_prefix.c_str()).found: 1;
    }
}
