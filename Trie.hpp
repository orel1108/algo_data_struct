#pragma once

#include <vector>
#include <string>

/**
 * @brief Implementation of Trie data structure (an efficient information reTrieval data structure).
 */
class Trie
{
public:
    /**
     * @brief Definition of Trie node.
     */
    struct TrieNode
    {
        int value;                         /**< Value stored in node. */
        std::vector<TrieNode *> child;     /**< Childrens of node.    */

        /**
         * @brief Constructor.
         * @param[in] i_size Alphabet size.
         */
        TrieNode(const std::size_t i_size)
            : value(0)
            , child(std::vector<TrieNode *>(i_size, nullptr))
        {}
    };

    /**
    * @brief Constructor.
    * @param[in] i_size Alphabet size.
    */
    Trie(const std::size_t i_size)
        : m_root(new TrieNode(i_size))
        , m_count(0)
        , m_size(i_size)
    {}

    /**
     * @brief Adds new key to Trie.
     * @param[in] i_key Key to be added.
     */
    void insert(const std::string & i_key);

    /**
     * @brief Searches key in Trie.
     * @param[in] i_key Key to be searched.
     * @return True if key is present in Trie or False otherwise.
     */
    bool search(const std::string & i_key) const;

    /**
     * @brief Removes key from Trie.
     * @param[in] Given key.
     */
    void delete_key(const std::string & i_key);

    /**
     * @brief Finds longest prefix of input string which is in Trie keys.
     * @param[in] i_key Key to be searched.
     * @return Key from Trie which is longest prefix of input key.
     */
    std::string longest_prefix(const std::string & i_key) const;

private:
    TrieNode * m_root;                     /**< Root of trie.            */
    std::size_t m_count;                   /**< Number of keys in Trie.  */
    std::size_t m_size;                    /**< Alphabet size.           */
};
