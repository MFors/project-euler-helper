/*

    Project Euler Helper v0.0.2
    Mikael Fors 2014

    type:     trees
    function: trie
    desc:     prefix tree for strings

*/

#include "trie.h"
#include <queue>

namespace project_euler_helper {

    /* ######## ------- NODE ------- ######## */

    TrieNode::TrieNode(const char* p_string) {
        m_count = 0;
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

    void TrieNode::insert(const char* p_string) {
        TrieNode *node = this;
        while(*p_string) {
            if(node->m_children.find(*p_string) != node->m_children.end()) {
                node = node->m_children[*p_string];
            } else {
                node->m_children[*p_string] = new TrieNode;
                node = node->m_children[*p_string];
            }
            ++p_string;
        }
        node->m_count++;
    }

    PrefixSearchResult TrieNode::find(const char* p_string) {
        TrieNode* node = this;
        while(*p_string) {
            if(node->m_children.find(*p_string) != node->m_children.end()) {
                node = node->m_children[*p_string];
            } else {
                (PrefixSearchResult){0, 0};
            }
            ++p_string;
        }
        return (PrefixSearchResult){1, node->m_count > 0};
    }

    std::vector<std::string> TrieNode::contentWithPrefix(const char* p_prefix) {

        TrieNode* node = this;
        std::vector<std::string> result{};
        std::string prefix{""};

        while(*p_prefix) {
            if(node->m_children.find(*p_prefix) != node->m_children.end()) {
                node = node->m_children[*p_prefix];
                prefix.push_back(*p_prefix);
                ++p_prefix;
            } else {
                return result;
            }
        }

        // If we are here, we found something and need to BFS
        std::queue<PrefixQueueItem> jobs{};
        jobs.push((PrefixQueueItem){node, prefix});
        PrefixQueueItem currentJob;

        while(!jobs.empty()) {
            currentJob = jobs.front();
            jobs.pop();
            if(currentJob.node && currentJob.node->m_count)
                result.push_back(currentJob.key);
            for(std::map<char,TrieNode*>::iterator child = currentJob.node->m_children.begin();
                child != currentJob.node->m_children.end(); ++child) {

                jobs.push((PrefixQueueItem){
                    child->second,
                    currentJob.key + std::string(1, child->first)
                });
            }
        }

        return result;
    }


    /* ######## ------- TREE ------- ######## */

    Trie::Trie(const std::vector<std::string>& p_strings) {
        if(p_strings.size()) {
            m_root = new TrieNode(p_strings[0].c_str());
            for(uint i = 1; i < p_strings.size(); ++i) {
                m_root->insert(p_strings[i].c_str());
            }
        } else {
            m_root = new TrieNode;
        }
    }

    Trie::~Trie() {
        delete m_root;
    }

    void Trie::insert(const std::string& p_string) {
        if(p_string.length())
            m_root->insert(p_string.c_str());
    }

    bool Trie::contains(const std::string& p_string) {
        return p_string.length() ? m_root-> find(p_string.c_str()).isLeaf : 0;

    }

    bool Trie::containsPrefix(const std::string& p_prefix) {
        return p_prefix.length() ? m_root -> find(p_prefix.c_str()).found: 1;
    }

    std::vector<std::string> Trie::contentWithPrefix(const char* p_prefix) {
        return m_root->contentWithPrefix(p_prefix);
    }
}
