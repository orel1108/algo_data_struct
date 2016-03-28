#include <string>

#include "Trie.hpp"

namespace
{
    /**
     * @brief Calculates position of character in alphabet.
     * @param[in] i_chr Input character.
     * @return Psition of character in alphabet.
     */
    int key_to_idx(const char i_chr)
    {
        return i_chr - 'a';
    }

    /**
     * @brief Checks wether node is a leaf node.
     * @param[in] i_node Trie node.
     * @return True if node is leaf node and False otherwise.
     */
    bool is_leaf(const Trie::TrieNode * const i_node)
    {
        return i_node->value > 0;
    }

    /**
     * @brief Check wether node has at least one child node.
     * @return True if node is free and False otherwise.
     */
    bool is_free_node(const Trie::TrieNode * const i_node)
    {
        for (std::size_t pos = 0; pos < i_node->child.size(); ++pos)
        {
            if (i_node->child[pos] != nullptr)
            {
                return true;
            }
        }

        return false;
    }

    /**
    * @brief Helper function.
    * @param[in] i_node Trie node.
    * @param[in] i_key Input Key.
    * @param[in] i_level Level where key is looking for.
    * @param[in] i_len Length of key.
    */
    bool delete_key_util(Trie::TrieNode * i_node, const std::string & i_key, std::size_t i_level, std::size_t i_len)
    {
        if (i_node != nullptr)
        {
            // base case
            if (i_level == i_len)
            {
                if (is_leaf(i_node))
                {
                    // unmark leaf node
                    i_node->value = 0;
                    if (is_free_node(i_node))
                    {
                        return true;
                    }
                    return false;
                }
            }
            else
            {
                // find index of child
                int idx = key_to_idx(i_key[i_level]);
                // recursively delete other nodes
                if (delete_key_util(i_node->child[idx], i_key, i_level + 1, i_len))
                {
                    // delete last node
                    delete i_node->child[idx];
                    i_node->child[idx] = nullptr;

                    return !is_leaf(i_node) && is_free_node(i_node);
                }
            }
        }

        return false;
    }
}

/**
* @brief Adds new key to Trie.
* @param[in] i_key Key to be added.
*/
void Trie::insert(const std::string & i_key)
{
    // increase number of keys
    m_count++;

    // copy root
    TrieNode * node = m_root;
    for (std::size_t level = 0; level < i_key.size(); ++level)
    {
        int idx = key_to_idx(i_key[level]);
        if (node->child[idx] == nullptr)
        {
            // create new node
            node->child[idx] = new TrieNode(m_size);
        }
        // move to next node
        node = node->child[idx];
    }

    // mark last node as leaf
    node->value = m_count;
}

/**
* @brief Searches key in Trie.
* @param[in] i_key Key to be searched.
* @return True if key is present in Trie or False otherwise.
*/
bool Trie::search(const std::string & i_key) const
{
    // copy root
    TrieNode * node = m_root;
    for (std::size_t level = 0; level < i_key.size(); ++level)
    {
        int idx = key_to_idx(i_key[level]);
        if (node->child[idx] == nullptr)
        {
            return 0;
        }
        // move to next node
        node = node->child[idx];
    }
    return (node != nullptr) && (node->value > 0);
}

/**
* @brief Removes key from Trie.
* @param[in] Given key.
*/
void Trie::delete_key(const std::string & i_key)
{
    const std::size_t n = i_key.size();
    if (n > 0)
    {
        delete_key_util(m_root, i_key, 0, n);
    }
}

/**
* @brief Finds longest prefix of input string which is in Trie keys.
* @param[in] i_key Key to be searched.
* @return Key from Trie which is longest prefix of input key.
*/
std::string Trie::longest_prefix(const std::string & i_key) const
{
    // longest prefix
    std::string pref;

    // copy root
    TrieNode * node = m_root;

    std::size_t prev_pos = 0;
    // traverse string
    for (std::size_t level = 0; level < i_key.size(); ++level)
    {
        int idx = key_to_idx(i_key[level]);

        if (node->child[idx] != nullptr)
        {
            pref += i_key[level];
            // move to next node
            node = node->child[idx];

            // store prevoius matching prefix
            if (is_leaf(node))
            {
                prev_pos = level + 1;
            }
        }
        else
        {
            break;
        }
    }

    // check if last node is leaf node
    if (!is_leaf(node))
    {
        return std::string(pref.begin(), pref.begin() + prev_pos);
    }

    return pref;
}
