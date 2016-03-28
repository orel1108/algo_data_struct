#pragma once

#include <string>

/**
 * @brief Definition of Ternary Search Tree. 
 */
struct Node
{
    char data;         /**< Data stored in node.       */
    bool is_end;       /**< Indicates end of string.   */
    Node * left;       /**< Pointer to left child.     */
    Node * eq;         /**< Pointer to equal child.    */
    Node * right;      /**< Pointer to right child.    */

    /**
     * @brief Tree node constructor.
     * @param[in] i_ch Character will be stored in node.
     */
    Node(char i_ch)
        : data(i_ch)
        , is_end(false)
        , left(nullptr)
        , eq(nullptr)
        , right(nullptr)
    {}
};

/**
 * @brief Definition of Ternary Search Tree.
 */
class TernarySearchTree
{
public:
    /**
     * @brief Default constructor.
     */
    TernarySearchTree()
        : m_root(nullptr)
    {}

    /**
     * @brief Adds new word into tree.
     * @param[in] i_word Word to be added.
     */
    void insert_word(const std::string & i_word);

    /**
     * @brief Searches word in tree.
     * @param[in] i_word Word to be searched.
     * @return True if word is present in tree and False otherwise.
     */
    bool search_word(const std::string & i_word) const;

    /**
     * @brief Ternary Search Tree traversal, prins all word in tree.
     */
    void traverse() const;

private:
    Node * m_root;     /**< Pointer to root of tree.   */
};