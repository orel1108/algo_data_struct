#include <string>
#include <iostream>

#include "TernarySearchTree.hpp"

namespace
{
    /**
     * @brief Utility function which adds new key into tree.
     * @param[in] i_root Pointer to the root of Ternary Search Tree.
     * @param[in] i_word Word to be added.
     * @param[in] i_depth Index in word.
     * @return New pointer to the root of Ternary Search Tree.
     */
    void insert_util(Node ** i_root, const std::string & i_word, const std::size_t i_depth)
    {
            // tree is empty
            if ((*i_root) == nullptr)
            {
                (*i_root) = new Node(i_word[i_depth]);
            }

            // insert into left subtree
            if (i_word[i_depth] < (*i_root)->data)
            {
                insert_util(&((*i_root)->left), i_word, i_depth);
            }
            // insert into right subtree
            else if (i_word[i_depth] > (*i_root)->data)
            {
                insert_util(&((*i_root)->right), i_word, i_depth);
            }
            // insert into equal subtree
            else
            {
                if (i_depth < i_word.size())
                {
                    insert_util(&((*i_root)->eq), i_word, i_depth + 1);
                }
                // if end of word reached
                else
                {
                    (*i_root)->is_end = true;
                }
            }
    }

    /**
    * @brief Utility function which searches key in tree.
    * @param[in] i_root Pointer to the root of Ternary Search Tree.
    * @param[in] i_word Word to be searched.
    * @param[in] i_depth Index in word.
    * @return True if word is found and False otherwise.
    */
    bool search_util(Node * i_root, const std::string & i_word, const std::size_t i_depth)
    {
        // empty tree
        if (i_root == nullptr)
        {
            return false;
        }

        // search in left tree
        if (i_word[i_depth] < i_root->data)
        {
            return search_util(i_root->left, i_word, i_depth);
        }

        // search in right tree
        if (i_word[i_depth] > i_root->data)
        {
            return search_util(i_root->right, i_word, i_depth);
        }

        // reach end of string
        if (i_depth == i_word.size())
        {
            return i_root->is_end;
        }

        return search_util(i_root->eq, i_word, i_depth + 1);
    }

    /**
    * @brief Utility function which traverse all keys in tree.
    * @param[in] i_root Pointer to the root of Ternary Search Tree.
    * @param[in] o_buff Output buffer.
    * @param[in] i_depth Index in word.
    */
    void traverse_util(Node * i_root, char * o_buff, const std::size_t i_depth)
    {
        if (i_root != nullptr)
        {
            // move to left tree
            traverse_util(i_root->left, o_buff, i_depth);

            o_buff[i_depth] = i_root->data;
            if (i_root->is_end)
            {
                o_buff[i_depth + 1] = '\0';
                std::cout << o_buff << std::endl;
            }

            // move to eq tree
            traverse_util(i_root->eq, o_buff, i_depth + 1);

            // move to right tree
            traverse_util(i_root->right, o_buff, i_depth);
        }
    }
}

/**
* @brief Adds new word into tree.
* @param[in] i_word Word to be added.
*/
void TernarySearchTree::insert_word(const std::string & i_word)
{
    insert_util(&m_root, i_word, 0);
}

/**
* @brief Searches word in tree.
* @param[in] i_word Word to be searched.
* @return True if word is present in tree and False otherwise.
*/
bool TernarySearchTree::search_word(const std::string & i_word) const
{
    return search_util(m_root, i_word, 0);
}

/**
* @brief Ternary Search Tree traversal, prins all word in tree.
*/
void TernarySearchTree::traverse() const
{
    char buff[1024];
    traverse_util(m_root, buff, 0);
}