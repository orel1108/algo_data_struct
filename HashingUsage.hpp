#pragma once

#include <vector>
#include <map>
#include <set>

/**
 * @brief Definition of binary tree node.
 * @tparam KeyType Type of keys strored in nodes.
 */
template<class KeyType>
struct TreeNode
{
    /**
     * @brief Tree node constructor.
     * @param[in] i_key Value of key.
     */
    TreeNode(const KeyType & i_key)
        : key(i_key)
        , left(nullptr)
        , right(nullptr)
    {}

    KeyType key;       /**< Key stored in node.     */
    TreeNode * left;   /**< Pointer to left child.  */
    TreeNode * right;  /**< Pointer to right child. */
};

/**
 * Brief Definiton of Singly Linked List.
 * @tparam KeyType Type of keys strored in nodes.
 */
template<class KeyType>
struct ListNode
{
    /**
    * @brief List node constructor.
    * @param[in] i_key Value of key.
    */
    ListNode(const KeyType & i_key)
        : key(i_key)
        , next(nullptr)
    {}

    KeyType key;       /**< Key stored in node.       */
    ListNode * next;   /**< Pointer to the next node. */
};

/**
 * @brief Add new key to tree (as in BST).
 * @tparam KeyType Type of keys strored in nodes.
 * @param[in] i_root Pointer to the root of binary tree.
 * @param[in] i_key Key to be added.
 * @return Pointer to the new root of tree.
 */
template<class KeyType>
TreeNode<KeyType> * insert(TreeNode<KeyType> * i_root, const KeyType & i_key)
{
    // if tree is empty or reach leaf
    if (i_root == nullptr)
    {
        return new TreeNode<KeyType>(i_key);
    }

    // insert into left subtree
    if (i_key < i_root->key)
    {
        i_root->left = insert(i_root->left, i_key);
    }
    else
    {
        i_root->right = insert(i_root->right, i_key);
    }

    return i_root;
}

/**
 * @brief Gets vertical order of binary tree.
 * @tparam KeyType Type of keys strored in nodes.
 * @param[in] i_root Pointer to binary tree root.
 * @param[out] o_vertical Vertical order of binary tree.
 * @param[in] i_dist Horizontal distance.
 */
template<class KeyType>
void verticalOrder(TreeNode<KeyType> * i_root, std::map<int, std::vector<KeyType>> & o_vertical, int i_dist)
{
    // base case
    if (i_root == nullptr)
    {
        return;
    }

    // add key
    o_vertical[i_dist].push_back(i_root->key);
    // recur left subtree, decrease horizontal distance by one
    verticalOrder(i_root->left, o_vertical, i_dist - 1);
    // recur right subtree, increase horizontal distance by one
    verticalOrder(i_root->right, o_vertical, i_dist + 1);
}

/**
 * @brief CHecks wether given set is subset of another set.
 * @tparam KeyType Type of keys strored in nodes.
 * @param[in] i_set Array of values.
 * @param[in] i_sub Array of values.
 * @return True if second array is subset of first array and False otherwise.
 */
template<class KeyType>
bool isSubset(const std::vector<KeyType> & i_set, const std::vector<KeyType> & i_sub)
{
    // contains number of occurrences of each value
    std::map<KeyType, int> counter;

    const std::size_t n = i_set.size();
    for (std::size_t pos = 0U; pos < n; ++pos)
    {
        counter[i_set[pos]]++;
    }

    const std::size_t m = i_sub.size();
    for (std::size_t pos = 0U; pos < m; ++pos)
    {
        // decrease conter
        if (counter[i_sub[pos]] > 0)
        {
            counter[i_sub[pos]]--;
        }
        // key not found
        else
        {
            return false;
        }
    }

    return true;
}

/**
 * @brief Adds new key at the front of list.
 * @param[in] i_head Pointer to the head of list.
 * @param[in] i_key Key to be added.
 * @return Pointer to new head of list.
 */
template<class KeyType>
ListNode<KeyType> * insert(ListNode<KeyType> * i_head, const KeyType & i_key)
{
    // list is empty
    if (i_head == nullptr)
    {
        return new ListNode<KeyType>(i_key);
    }

    // create new node
    ListNode<KeyType> * head = new ListNode<KeyType>(i_key);
    // create link to head
    head->next = i_head;

    return head;
}

/**
 * @brief Union of two linked lists.
 * @param[in] i_left Pointer to head of first list.
 * @param[in] i_right Pointer to head of second list.
 * @return Pointer to head of new list which contains union of two lists.
 */
template<class KeyType>
ListNode<KeyType> * unionLists(ListNode<KeyType> * i_left, ListNode<KeyType> * i_right)
{
    // base cases
    if (i_left == nullptr)
    {
        return i_right;
    }
    if (i_right == nullptr)
    {
        return i_left;
    }

    // keys of first list
    std::set<KeyType> s;

    // traverse first list
    while (i_left != nullptr)
    {
        // add key
        s.insert(i_left->key);
        // move to next node
        i_left = i_left->next;
    }

    // traverse second list
    while (i_right != nullptr)
    {
        // add key
        s.insert(i_right->key);
        // move to next node
        i_right = i_right->next;
    }

    // union of lists
    ListNode<KeyType> * head = nullptr;

    std::set<KeyType>::iterator it = s.begin();
    // traverse set of keys and add to list
    for (; it != s.end(); ++it)
    {
        head = insert(head, *it);
    }

    return head;
}

/**
* @brief Intersection of two linked lists.
* @param[in] i_left Pointer to head of first list.
* @param[in] i_right Pointer to head of second list.
* @return Pointer to head of new list which contains intersection of two lists.
*/
template<class KeyType>
ListNode<KeyType> * intersectionLists(ListNode<KeyType> * i_left, ListNode<KeyType> * i_right)
{
    // base cases
    if (i_left == nullptr || i_right == nullptr)
    {
        return nullptr;
    }
    
    // keys of first list
    std::set<KeyType> s;

    // traverse first list
    while (i_left != nullptr)
    {
        // add key
        s.insert(i_left->key);
        // move to next node
        i_left = i_left->next;
    }

    // union of lists
    ListNode<KeyType> * head = nullptr;

    // traverse second list
    while (i_right != nullptr)
    {
        if (s.find(i_right->key) != s.end())
        {
            head = insert(head, i_right->key);
        }
        // move to next node
        i_right = i_right->next;
    }

    return head;
}

/**
 * @brief Checks wether array has duplicates with distance at most k.
 * @param[in] i_arr Input array.
 * @param[in] i_k Maximal distance.
 * @return True if array has duplicates within given range and False otherwise.
 */
template<class KeyType>
bool hasDuplicatesWithinK(const std::vector<KeyType> & i_arr, const std::size_t i_k)
{
    // auxiliary data structure
    std::set<KeyType> s;

    const std::size_t n = i_arr.size();
    for (std::size_t pos = 0U; pos < n; ++pos)
    {
        // found duplicate
        if (s.find(i_arr[pos]) != s.end())
        {
            return true;
        }

        // add new element
        s.insert(i_arr[pos]);

        // remove element that is out of range
        if (pos >= i_k)
        {
            s.erase(s.find(i_arr[pos - i_k]));
        }
    }

    return false;
}
