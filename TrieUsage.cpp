#include <string>

#include "TrieUsage.hpp"

namespace
{
    /**
     * @brief Converts character to index.
     * @param[in] i_chr Input character.
     * @return Index of character.
     */
    int idx(char i_chr)
    {
        return (i_chr == '.') ? 10 : (i_chr - '0');
    }
}

/**
* @brief Add IP address and corresponding URL.
* @param[in] i_ip IP address.
* @param[in] i_url URL.
*/
void ReverseDNSCache::insert(const std::string & i_ip, const std::string & i_url)
{
    // copy root
    Node * node = m_root;

    for (std::size_t level = 0; level < i_ip.size(); ++level)
    {
        // get index of character
        int index = idx(i_ip[level]);

        if (node->child[index] == nullptr)
        {
            // create new node
            node->child[index] = new Node;
        }

        // move to next node
        node = node->child[index];
    }

    // set URL
    node->url = i_url;
    // mark node as leaf node
    node->is_leaf = true;
}

/**
* @brief Reverse DNS search.
* @param[in] i_ip IP address.
* @return URL which corresponds to given IP.
*/
std::string ReverseDNSCache::search(const std::string & i_ip) const
{
    // copy root
    Node * node = m_root;

    for (std::size_t level = 0; level < i_ip.size(); ++level)
    {
        // get index of character
        int index = idx(i_ip[level]);

        // IP not found
        if (node->child[index] == nullptr)
        {
            return std::string("IP not found");
        }

        // move to next node
        node = node->child[index];
    }

    // found IP
    if (node != nullptr && node->is_leaf)
    {
        return node->url;
    }

    return std::string("IP not found");
}
