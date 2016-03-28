#pragma once

#include <cstddef>
#include <algorithm>
#include <iostream>

/**
* @brief AVL tree node definition.
* @tparam KeyType Type of keys stored in tree nodes.
*/
template<class KeyType>
struct Node
{
    KeyType key;           /**< Data stored in tree node.               */
    Node * left;           /**< Pointer to the left child.              */
    Node * right;          /**< Pointer to the right child.             */
    std::size_t height;    /**< Height of tree rooted at this node.     */
    std::size_t count;     /**< Count duplicate keys.                   */

    /**
     * @brief Tree node constructor.
     * @param[in] i_key Key to be stored in tree node.
     */
    Node(const KeyType & i_key)
        : key(i_key)
        , left(nullptr)
        , right(nullptr)
        , height(1)
        , count(1)
    {}
};

/**
 * @brief Calculates height of tree.
 * @tparam KeyType Type of keys stored in tree nodes.
 * @param[in] i_root Pointer to the root of tree.
 * @return Height of tree.
 */
template<class KeyType>
std::size_t height(Node<KeyType> * i_root)
{
    // tree is empty
    if (i_root == nullptr)
    {
        return 0U;
    }

    return i_root->height;
}

/**
* @brief Calculates balance of tree.
* @tparam KeyType Type of keys stored in tree nodes.
* @param[in] i_root Pointer to the root of tree.
* @return Difference between left and right subtrees.
*/
template<class KeyType>
int balance(Node<KeyType> * i_root)
{
    // tree is empty
    if (i_root == nullptr)
    {
        return 0U;
    }

    return static_cast<int>(height(i_root->left)) - static_cast<int>(height(i_root->right));
}

/**
 * @brief Gets minimum value in tree.
 * @tparam KeyType Type of keys stored in tree nodes.
 * @param[in] i_root Pointer to the root of tree.
 * @return Pointer to node with minimal value in tree.
 */
template<class KeyType>
Node<KeyType> * min_value(Node<KeyType> * i_root)
{
    typename Node<KeyType> * node = i_root;

    // always move to the left
    while (node != nullptr && node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

/**
*      y                  x
*     / \                / \
*    x   t3   ----->    t1  y
*   / \                    / \
*  t1  t2                 t2  t3
* @brief Perfroms right rotation.
* @tparam KeyType Type of keys stored in tree nodes.
* @param[in] y Pointer to the root of tree.
* @return Node root of rotated tree.
*/
template<class KeyType>
Node<KeyType> * rotate_right(Node<KeyType> * y)
{
    // get left subtree
    typename Node<KeyType> * x = y->left;
    // get right subtree of left subtree
    typename Node<KeyType> * t2 = x->right;

    // rotate
    x->right = y;
    y->left = t2;

    // update heights
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

/**
*      x                  y
*     / \                / \
*    t1   y   ----->    x   t3
*        / \           / \
*       t2  t3        t1  t2
* @brief Perfroms left rotation.
* @tparam KeyType Type of keys stored in tree nodes.
* @param[in] x Pointer to the root of tree.
* @return Node root of rotated tree.
*/
template<class KeyType>
Node<KeyType> * rotate_left(Node<KeyType> * x)
{
    // get right subtree
    typename Node<KeyType> * y = x->right;
    // get left subtree of right subtree
    typename Node<KeyType> * t2 = y->left;

    // rotate
    y->left = x;
    x->right = t2;

    // update heights
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

/**
 * @brief Add new key to AVL tree.
 * @tparam KeyType Type of keys stored in tree nodes.
 * @param[in] i_root Pointer to the root of tree.
 * @param[in] i_key Key to be added.
 * @return Pointer to the new root of tree.
 */
template<class KeyType>
Node<KeyType> * insert_key(Node<KeyType> * i_root, const KeyType & i_key)
{
    // case when tree is empty
    if (i_root == nullptr)
    {
        return new Node<KeyType>(i_key);
    }

    // found duplicate
    if (i_root->key == i_key)
    {
        (i_root->count)++;
        return i_root;
    }

    // insert into left subtree
    if (i_root->key > i_key)
    {
        i_root->left = insert_key(i_root->left, i_key);
    }
    // insert into right subtree
    else
    {
        i_root->right = insert_key(i_root->right, i_key);
    }

    // update height
    i_root->height = std::max(height(i_root->left), height(i_root->right)) + 1;

    // get balance of tree
    int b = balance(i_root);

    // left-left case
    if (b > 1 && i_key < i_root->left->key)
    {
        return rotate_right(i_root);
    }

    // right-right case
    if (b < -1 && i_key > i_root->right->key)
    {
        return rotate_left(i_root);
    }

    // left-right case
    if (b > 1 && i_key > i_root->left->key)
    {
        i_root->left = rotate_left(i_root->left);
        return rotate_right(i_root);
    }

    // right-left case
    if (b < -1 && i_key < i_root->right->key)
    {
        i_root->right = rotate_right(i_root->right);
        return rotate_left(i_root);
    }

    return i_root;
}

/**
* @brief Removes key from AVL tree.
* @tparam KeyType Type of keys stored in tree nodes.
* @param[in] i_root Pointer to the root of tree.
* @param[in] i_key Key to be removed.
* @return Pointer to the new root of tree.
*/
template<class KeyType>
Node<KeyType> * delete_key(Node<KeyType> * i_root, const KeyType & i_key)
{
    // tree is empty
    if (i_root == nullptr)
    {
        return i_root;
    }

    // move to left subtree
    if (i_key < i_root->key)
    {
        i_root->left = delete_key(i_root->left, i_key);
    }
    // move to right subtree
    else if (i_key > i_root->key)
    {
        i_root->right = delete_key(i_root->right, i_key);
    }
    // found key, node will be deleted
    else
    {
        // if duplicate is found, decrement counter and return
        if (i_root->count > 1)
        {
            (i_root->count)--;
            return i_root;
        }

        // node with only one child or no child
        if ((i_root->left == nullptr) || (i_root->right == nullptr))
        {
            typename Node<KeyType> * node = i_root->left ? i_root->left : i_root->right;

            // no child case
            if (node == nullptr)
            {
                node = i_root;
                i_root = nullptr;
            }
            // one child case
            else
            {
                *i_root = *node;
            }

            // free memory
            delete node;
            node = nullptr;
        }
        else
        {
            // node with two children
            typename Node<KeyType> * node = min_value(i_root->right);

            // copy the inorder successor's data to this node
            i_root->key = node->key;

            // delete the inorder successor
            i_root->right = delete_key(i_root->right, node->key);
        }
    }

    // if the tree had only one node then return
    if (i_root == nullptr)
    {
        return i_root;
    }

    // update height
    i_root->height = std::max(height(i_root->left), height(i_root->right)) + 1;

    // get balance
    int b = balance(i_root);

    // left-left case
    if (b > 1 && balance(i_root->left) >= 0)
    {
        return rotate_right(i_root);
    }

    // left-right case
    if (b > 1 && balance(i_root->left) < 0)
    {
        i_root->left = rotate_left(i_root->left);
        return rotate_right(i_root);
    }

    // right-right case
    if (b < -1 && balance(i_root->right) <= 0)
    {
        return rotate_left(i_root);
    }

    // right-left case
    if (b < -1 && balance(i_root->right) > 0)
    {
        i_root->right = rotate_right(i_root->right);
        return rotate_left(i_root);
    }

    return i_root;
}

/**
 * @brief Preforms preorder tree traversal.
 * @tparam KeyType Type of keys stored in tree nodes.
 * @param[in] i_root Pointer to the root of tree.
 */
template<class KeyType>
void pre_order(Node<KeyType> * i_root)
{
    if (i_root != nullptr)
    {
        std::cout << i_root->key << "(" << i_root->count << ") ";
        pre_order(i_root->left);
        pre_order(i_root->right);
    }
}

/**
 * @brief AVL tree implementation.
 * @tparam KeyType Type of keys stored in tree nodes.
 */
template<class KeyType>
class AVLTree
{
public:
    /**
     * @brief Default constructor for AVL tree.
     */
    AVLTree()
        : m_root(nullptr)
    {}

    /**
     * @brief Adds new key to AVL tree.
     * @param[in] i_key Key to be added.
     */
    void insert_key(const KeyType & i_key)
    {
        m_root = ::insert_key(m_root, i_key);
    }

    /**
    * @brief Removes key from AVL tree.
    * @param[in] i_key Key to be removed.
    */
    void delete_key(const KeyType & i_key)
    {
        m_root = ::delete_key(m_root, i_key);
    }

    /**
    * @brief Preforms preorder tree traversal.
    */
    void preorder() const
    {
        ::pre_order(m_root);
    }

private:
    typename Node<KeyType> * m_root;             /**< Pointer to the root node.    */
};
