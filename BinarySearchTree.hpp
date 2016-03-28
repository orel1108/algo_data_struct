#pragma once

#include <queue>
#include <stack>
#include <algorithm>

/**
* @brief Definition of tree node.
* @tparam KeyType Type of value stored in nodes.
*/
template<class KeyType>
struct TNode
{
    KeyType key;           /**< Key stored in tree node. */
    struct TNode * left;   /**< Left child.              */
    struct TNode * right;  /**< Right child.             */
};

/**
* @brief Performs pre-order tree traversal.
* @tparam KeyType Type of keys in nodes.
* @tparam VisitFunc Type of unary function.
* @param[in] i_root Root of binary tree.
* @param[in] i_func Operation which will be applied to keys in nodes.
*/
template<class KeyType, class VisitFunc>
void preorder(const TNode<KeyType> * const i_root, VisitFunc i_func)
{
    // empty tree
    if (i_root == nullptr)
    {
        return;
    }

    // process node
    i_func(i_root->key);

    // recur left subtree
    preorder(i_root->left, i_func);

    // recur right subtree
    preorder(i_root->right, i_func);
}

/**
* @brief Performs in-order tree traversal.
* @tparam KeyType Type of keys in nodes.
* @tparam VisitFunc Type of unary function.
* @param[in] i_root Root of binary tree.
* @param[in] i_func Operation which will be applied to keys in nodes.
*/
template<class KeyType, class VisitFunc>
void inorder(const TNode<KeyType> * const i_root, VisitFunc i_func)
{
    // empty tree
    if (i_root == nullptr)
    {
        return;
    }

    // recur left subtree
    inorder(i_root->left, i_func);

    // process node
    i_func(i_root->key);

    // recur right subtree
    inorder(i_root->right, i_func);
}

/**
* @brief Performs post-order tree traversal.
* @tparam KeyType Type of keys in nodes.
* @tparam VisitFunc Type of unary function.
* @param[in] i_root Root of binary tree.
* @param[in] i_func Operation which will be applied to keys in nodes.
*/
template<class KeyType, class VisitFunc>
void postorder(const TNode<KeyType> * const i_root, VisitFunc i_func)
{
    // empty tree
    if (i_root == nullptr)
    {
        return;
    }

    // recur left subtree
    postorder(i_root->left, i_func);

    // recur right subtree
    postorder(i_root->right, i_func);

    // process node
    i_func(i_root->key);
}

/**
* @brief Performs level-order tree traversal (BFS).
* @tparam KeyType Type of keys in nodes.
* @tparam VisitFunc Type of unary function.
* @param[in] i_root Root of binary tree.
* @param[in] i_func Operation which will be applied to keys in nodes.
*/
template<class KeyType, class VisitFunc>
void levelorder(TNode<KeyType> * i_root, VisitFunc i_func)
{
    // empty tree
    if (i_root == nullptr)
    {
        return;
    }

    // auxiliary data structure
    std::queue<TNode<KeyType> *> q;
    // enqueue root
    q.push(i_root);

    // traverse tree level-by-level
    while (!q.empty())
    {
        // dequeue top node
        TNode<KeyType> * node = q.front();
        q.pop();

        // process key
        i_func(node->key);

        // enqueue left child
        if (node->left != nullptr)
        {
            q.push(node->left);
        }

        // enqueue right child
        if (node->right != nullptr)
        {
            q.push(node->right);
        }
    }
}

/**
* @brief Performs tree traversal in nodes which are at k distance from root.
* @tparam KeyType Type of keys in nodes.
* @tparam VisitFunc Type of unary function.
* @param[in] i_root Root of binary tree.
* @param[in] i_func Operation which will be applied to keys in nodes.
* @param[in] i_level Distance from root.
*/
template<class KeyType, class VisitFunc>
void kthLevel(TNode<KeyType> * i_root, VisitFunc i_func, std::size_t i_level)
{
    // case of empty tree
    if (i_root == nullptr)
    {
        return;
    }

    // process node
    if (i_level == 0U)
    {
        i_func(i_root->key);
        return;
    }
    else
    {
        // process nodes in left subtree
        kthLevel(i_root->left, i_func, i_level - 1);
        // process nodes in right subtree
        kthLevel(i_root->right, i_func, i_level - 1);
    }
}

/**
* @brief Processes all ancestors of node with given key.
* @tparam KeyType Type of keys in nodes.
* @tparam VisitFunc Type of unary function.
* @param[in] i_root Root of binary tree.
* @param[in] i_key Key to be searched.
* @param[in] i_func Operation which will be applied to keys in nodes.
* @return True if key was found and False otherwise.
*/
template<class KeyType, class VisitFunc>
bool processAncestors(TNode<KeyType> * i_root, const KeyType & i_key, VisitFunc i_func)
{
    // case of empty tree
    if (i_root == nullptr)
    {
        return false;
    }

    // found key
    if (i_root->key == i_key)
    {
        return true;
    }

    // if key found in left or right subtree
    if (processAncestors(i_root->left, i_key, i_func) || processAncestors(i_root->right, i_key, i_func))
    {
        // process key
        i_func(i_root->key);
        return true;
    }

    return false;
}

/**
* @brief Calculates height of binary tree.
* @tparam KeyType Type of keys stored in nodes.
* @param[in] i_root Root of binary tree.
* @return Height of binary tree.
*/
template<class KeyType>
std::size_t height(const TNode<KeyType> * const i_root)
{
    // height of empty tree is 0
    if (i_root == nullptr)
    {
        return 0U;
    }
    // recursively call height on left and right childs
    return 1U + std::max(height(i_root->left), height(i_root->right));
}

/**
* @brief Calculates diameter of binary tree (maximal distance between leafs).
* @tparam KeyType Type of keys stored in nodes.
* @param[in] i_root Root of binary tree.
* @return Diameter of binary tree.
*/
template<class KeyType>
std::size_t diameter(const TNode<KeyType> * const i_root)
{
    // height of empty tree is 0
    if (i_root == nullptr)
    {
        return 0U;
    }

    // height of left subtree
    const std::size_t lh = height(i_root->left);
    // height of right subtree
    const std::size_t rh = height(i_root->right);

    // diameter of left subtree
    const std::size_t ld = diameter(i_root->left);
    // diameter of right subtree
    const std::size_t rd = diameter(i_root->right);

    // diameter is maximum of: diameter of left subtree, diameter of right subtree and 
    // height of left subtree + height of right subtree + 1
    return std::max({ 1U + lh + rh, ld, rd });
}

/**
* @brief Calculates diameter of binary tree (maximal distance between leafs), optimized version.
* @tparam KeyType Type of keys stored in nodes.
* @param[in] i_root Root of binary tree.
* @param[in] io_height Height of binary tree.
* @return Diameter of binary tree.
*/
template<class KeyType>
std::size_t diameter_optimized(const TNode<KeyType> * const i_root, std::size_t * io_height)
{
    // height of left and right subtrees
    std::size_t lh = 0U, rh = 0U;

    // height and diameter of empty tree are 0
    if (i_root == nullptr)
    {
        *io_height = 0U;
        return 0;
    }

    // diameter of left subtree
    const std::size_t ld = diameter_optimized(i_root->left, &lh);
    // diameter of right subtree
    const std::size_t rd = diameter_optimized(i_root->right, &rh);

    // get height of tree
    *io_height = std::max(lh, rh) + 1;

    // diameter is maximum of: diameter of left subtree, diameter of right subtree and 
    // height of left subtree + height of right subtree + 1
    return std::max({ 1U + lh + rh, ld, rd });
}

/**
* @brief Inserts new key into binary tree.
* @tparam KeyType Type of keys stored in nodes.
* @param[in,out] io_root Root of binary tree.
* @param[in] i_key Key to be inserted.
*/
template<class KeyType>
void insert(TNode<KeyType> ** io_root, const KeyType & i_key)
{
    // if tree is empty
    if (*io_root == nullptr)
    {
        // create new root
        (*io_root) = new TNode<KeyType>;
        (*io_root)->key = i_key;
        (*io_root)->left = nullptr;
        (*io_root)->right = nullptr;
    }
    // insert into left subtree
    else if ((*io_root)->key > i_key)
    {
        insert(&((*io_root)->left), i_key);
    }
    // insert into right subtree
    else
    {
        insert(&((*io_root)->right), i_key);
    }
}

/**
* @brief Searches key in BST.
* @tparam KeyType Type of keys stored in nodes.
* @param[in] i_root Root of binary search tree.
* @param[in] i_key Key to be find.
*/
template<class KeyType>
TNode<KeyType> * search(TNode<KeyType> * i_root, const KeyType & i_key)
{
    // empty tree
    if (i_root == nullptr)
    {
        return nullptr;
    }

    // found key
    if (i_root->key == i_key)
    {
        return i_root;
    }

    // if key is less then key in root move to left subtree
    if (i_root->key > i_key)
    {
        return search(i_root->left, i_key);
    }

    // traverse right subtree
    return search(i_root->right, i_key);
}

/**
* @brief Makes binary empty.
* @tparam KeyType Type of keys stored in nodes.
* @param[in,out] io_root Root of binary tree.
*/
template<class KeyType>
void clear(TNode<KeyType> ** io_root)
{
    // if tree is empty then nothing to do
    if (*io_root == nullptr)
    {
        return;
    }

    // recur left subtree
    clear(&(*io_root)->left);
    // recur right subtree
    clear(&(*io_root)->right);

    // free memory
    delete *io_root;
    *io_root = nullptr;
}

/**
* @brief Performs in-order tree traversal without recursion.
* @tparam KeyType Type of keys in nodes.
* @tparam VisitFunc Type of unary function.
* @param[in] i_root Root of binary tree.
* @param[in] i_func Operation which will be applied to keys in nodes.
*/
template<class KeyType, class VisitFunc>
void inorder_iter(TNode<KeyType> * i_root, VisitFunc i_func)
{
    // if tree is empty nothing to do
    if (i_root == nullptr)
    {
        return;
    }

    // auxiliary data structure
    std::stack<TNode<KeyType> *> st;
    // current node
    TNode<KeyType> * node = i_root;

    // traverse tree nodes
    while (true)
    {
        // push left child
        if (node != nullptr)
        {
            st.push(node);
            // move to left subtree
            node = node->left;
        }
        else
        {
            if (!st.empty())
            {
                // remove top node
                node = st.top();
                st.pop();

                // process node's keys
                i_func(node->key);

                // move to right subtree
                node = node->right;
            }
            else
            {
                break;
            }
        }
    }
}


/**
* @brief Clones binary tree.
* @tparam KeyType Type of keys in nodes.
* @param[in] i_root Root of binary tree.
* @return Copy of binary tree.
*/
template<class KeyType>
TNode<KeyType> * clone(TNode<KeyType> * i_root)
{
    // if tree is empty nothing to do
    if (i_root == nullptr)
    {
        return nullptr;
    }

    // create new root
    TNode<KeyType> * root = new TNode<KeyType>();
    // copy key
    root->key = i_root->key;
    // copy left subtree
    root->left = clone(i_root->left);
    // copy right subtree
    root->right = clone(i_root->right);

    return root;
}

/**
* @brief Contructs tree binary tree from in-order and pre-order traversals.
* @tparam KeyType Type of keys in nodes.
* @param[in] i_inorder In-order tree traversal.
* @param[in] i_preorder Pre-order tree traversal.
* @param[in] i_start Start index.
* @param[in] i_end End index.
* @return Root of binary tree.
*/
template<class KeyType>
TNode<KeyType> * buildTreeInPreOrder(const std::vector<KeyType> & i_inorder, const std::vector<KeyType> & i_preorder, int i_start, int i_end)
{
    // current index in preorder traversal
    static int pre_idx = 0;

    if (i_start > i_end)
    {
        return nullptr;
    }

    // create new node
    TNode<KeyType> * node = new TNode<KeyType>();
    // set key and increment index in preorder
    node->key = i_preorder[pre_idx++];

    // node has no childs
    if (i_start == i_end)
    {
        return node;
    }

    // find index of node in inorder traversal, then left indeces will be in left subtree and right indeces will be in right subtree
    int in_idx = std::distance(i_inorder.begin(), std::find(i_inorder.begin(), i_inorder.end(), node->key));

    // build left subtree
    node->left = buildTreeInPreOrder(i_inorder, i_preorder, i_start, in_idx - 1);
    // build right subtree
    node->right = buildTreeInPreOrder(i_inorder, i_preorder, in_idx + 1, i_end);

    return node;
}

/**
* @brief Calculates width of tree at given level.
* @tparam KeyType Type of keys in nodes.
* @param[in] i_root Root of binary tree.
* @param[in] i_level Level of tree.
* @return Width of tree at given level.
*/
template<class KeyType>
std::size_t widthAtLevel(TNode<KeyType> * i_root, std::size_t i_level)
{
    // width of empty tree is 0
    if (i_root == nullptr)
    {
        return 0U;
    }

    // width of root is 1
    if (i_level == 1U)
    {
        return 1U;
    }
    // width of left subtree + width of right subtree
    return widthAtLevel(i_root->left, i_level - 1) + widthAtLevel(i_root->right, i_level - 1);
}

/**
* @brief Calculates maximal width of binary tree.
* @tparam KeyType Type of keys in nodes.
* @param[in] i_root Root of binary tree.
* @return Maximal width of binary tree.
*/
template<class KeyType>
std::size_t maxWidth(TNode<KeyType> * i_root)
{
    std::size_t w = 0U;
    std::size_t h = height(i_root);

    // traverse all levels
    for (std::size_t H = 1U; H <= h; H++)
    {
        // get width at current level
        std::size_t cw = widthAtLevel(i_root, H);
        // find maximum
        if (cw > w)
        {
            w = cw;
        }
    }

    return w;
}

/**
* @brief Calculates maximum width recursively and result into array.
* @tparam KeyType Type of keys in nodes.
* @param[in] i_root Root of binary tree.
* @param[in,out] io_count Contains count of nodes at each level.
* @param[in] i_level Level in tree.
*/
template<class KeyType>
void maxWidthRecursive(TNode<KeyType> * i_root, std::vector<std::size_t> & io_count, std::size_t i_level)
{
    if (i_root != nullptr)
    {
        // increment number of nodes at level
        io_count[i_level]++;
        // recursively go to left subtree
        maxWidthRecursive(i_root->left, io_count, i_level + 1);
        // recursively go to right subtree
        maxWidthRecursive(i_root->right, io_count, i_level + 1);
    }
}

/**
* @brief Calculates maximal width of binary tree (optimized version).
* @tparam KeyType Type of keys in nodes.
* @param[in] i_root Root of binary tree.
* @return Maximal width of binary tree.
*/
template<class KeyType>
std::size_t maxWidthOptimized(TNode<KeyType> * i_root)
{
    // get height of tree
    const std::size_t h = height(i_root);

    // count number of nodes at each level
    std::vector<std::size_t> count(h);

    // start from 0 level
    maxWidthRecursive(i_root, count, 0);

    return *std::max_element(count.begin(), count.end());
}

/**
* @brief Checks wether binary trees are identical.
* @tparam KeyType Type of keys in nodes.
* @param[in] i_root1 Root of first tree.
* @param[in] i_root2 Root of second tree.
* @return True if trees are same and False otherwise.
*/
template<class KeyType>
bool areSame(TNode<KeyType> * i_root1, TNode<KeyType> * i_root2)
{
    // empty trees are identical
    if (i_root1 == nullptr && i_root2 == nullptr)
    {
        return true;
    }

    // case if only one is empty
    if (i_root1 == nullptr || i_root2 == nullptr)
    {
        return false;
    }

    // compare keys and left and right subtrees
    return (i_root1->key == i_root2->key) && areSame(i_root1->left, i_root2->left) && areSame(i_root1->right, i_root2->right);
}

/**
* @brief Checks wether tree is subtree of given tree.
* @tparam KeyType Type of keys in nodes.
* @param[in] i_tree Root of tree.
* @param[in] i_subtree Root of subtree.
* @return True if tree is subtree of given tree and False otherwise.
*/
template<class KeyType>
bool isSubtree(TNode<KeyType> * i_tree, TNode<KeyType> * i_subtree)
{
    // case when subtree is empty
    if (i_subtree == nullptr)
    {
        return true;
    }

    // case when tree is empty
    if (i_tree == nullptr)
    {
        return false;
    }

    // check tree with current root
    if (areSame(i_tree, i_subtree))
    {
        return true;
    }

    // check if subtree of left or right subtrees
    return areSame(i_tree->left, i_subtree) || areSame(i_tree->right, i_subtree);
}

/**
 * @brief Finds node with minimal value in BST.
 * @tparam KeyType Type of keys in nodes.
 * @param[in] i_root Root of tree.
 * @return Node with minimum key.
 */
template<class KeyType>
TNode<KeyType> * minNode(TNode<KeyType> * i_root)
{
    // if tree is empty
    if (i_root == nullptr)
    {
        return i_root;
    }

    TNode<KeyType> * root = i_root;
    // go to leftmost node
    while (root->left != nullptr)
    {
        root = root->left;
    }
    return root;
}

/**
 * @brief Removes node with given key from BST.
 * @tparam KeyType Type of keys in nodes.
 * @param[in] i_root Root of tree.
 * @param[in] i_key Key to be removed.
 * @return New root of tree.
 */
template<class KeyType>
TNode<KeyType> * delete_node(TNode<KeyType> ** i_root, const KeyType & i_key)
{
    // case when tree is empty
    if (*i_root == nullptr)
    {
        return *i_root;
    }

    // search key in left subtree
    if (i_key < (*i_root)->key)
    {
        (*i_root)->left = delete_node(&(*i_root)->left, i_key);
    }
    // search key in right subtree
    else if (i_key >(*i_root)->key)
    {
        (*i_root)->right = delete_node(&(*i_root)->right, i_key);
    }
    // key is found, now need to delete
    else
    {
        // process nodes with 0 or 1 childs
        if ((*i_root)->left == nullptr)
        {
            TNode<KeyType> * node = (*i_root)->right;

            // delete node
            delete (*i_root);
            *i_root = nullptr;

            return node;
        }
        else if ((*i_root)->right == nullptr)
        {
            TNode<KeyType> * node = (*i_root)->left;

            // delete node
            delete (*i_root);
            *i_root = nullptr;

            return node;
        }

        // search minimum inorder successor in the right subtree
        TNode<KeyType> * min_node = minNode((*i_root)->right);

        // copy key
        (*i_root)->key = min_node->key;

        // delete minimum node from right subtree
        (*i_root)->right = delete_node(&(*i_root)->right, min_node->key);
    }

    return *i_root;
}

/**
 * @brief Finds predecessor and accessor of given key in in-order traversal.
 * @tparam KeyType Type of keys in nodes.
 * @param[in] i_root Root of BST.
 * @param[out] o_pred Predecessor of given key.
 * @param[out] o_succ Successor of given key.
 * @param[in] i_key Value of key.
 */
template<class KeyType>
void findPredecessorAndSuccessor(TNode<KeyType> * i_root, TNode<KeyType> ** o_pred, TNode<KeyType> ** o_succ, const KeyType & i_key)
{
    // case of empty tree
    if (i_root == nullptr)
    {
        return;
    }

    // found key
    if (i_root->key == i_key)
    {
        // maximum value in left subtree is predecessor
        if (i_root->left != nullptr)
        {
            TNode<KeyType> * node = i_root->left;
            // maximum value is in the right most node
            while (node->right != nullptr)
            {
                node = node->right;
            }
            *o_pred = node;
        }

        // minimum value in right subtree is accessor
        if (i_root->right != nullptr)
        {
            TNode<KeyType> * node = i_root->right;
            // minimum value is in the left most node
            while (node->left != nullptr)
            {
                node = node->left;
            }
            *o_succ = node;
        }
        return;
    }

    if (i_root->key > i_key)
    {
        // store previous successor
        *o_succ = i_root;
        // recursively traverse left subtree
        findPredecessorAndSuccessor(i_root->left, o_pred, o_succ, i_key);
    }
    else
    {
        // store previous predecessor
        *o_pred = i_root;
        // recursively traverse right subtree
        findPredecessorAndSuccessor(i_root->right, o_pred, o_succ, i_key);
    }
}

/**
 * @brief Finds Lowest Common Ancestor for given values (Recursive version).
 * In BST the LCA will be the first key which lies between given keys.
 * @tparam KeyType Type of keys in nodes.
 * @param[in] i_root Root of BST.
 * @param[in] i_left First key.
 * @param[in] i_right Second key.
 * @return Lowest common ancestor if both keys are present and NULL otherwise.
 */
template<class KeyType>
TNode<KeyType> * lcaRecur(TNode<KeyType> * i_root, const KeyType & i_left, const KeyType & i_right)
{
    // case when tree is empty
    if (i_root == nullptr)
    {
        return i_root;
    }

    // if two key less then root's key then LCA is in left subtree
    if (i_root->key > i_left && i_root->key > i_right)
    {
        return lcaRecur(i_root->left, i_left, i_right);
    }

    // if two key greater then root's key then LCA is in right subtree
    if (i_root->key < i_left && i_root->key < i_right)
    {
        return lcaRecur(i_root->right, i_left, i_right);
    }

    // if both keys present return root
    if (search(i_root, i_left) != nullptr && search(i_root, i_right) != nullptr)
    {
        return i_root;
    }

    // at least one key is not present
    return nullptr;
}

/**
* @brief Finds Lowest Common Ancestor for given values (Iterative version).
* In BST the LCA will be the first key which lies between given keys.
* @tparam KeyType Type of keys in nodes.
* @param[in] i_root Root of BST.
* @param[in] i_left First key.
* @param[in] i_right Second key.
* @return Lowest common ancestor if both keys are present and NULL otherwise.
*/
template<class KeyType>
TNode<KeyType> * lcaIter(TNode<KeyType> * i_root, const KeyType & i_left, const KeyType & i_right)
{
    while (i_root != nullptr)
    {
        // if two key less then root's key then LCA is in left subtree
        if (i_root->key > i_left && i_root->key > i_right)
        {
            i_root = i_root->left;
        }

        // if two key greater then root's key then LCA is in right subtree
        else if (i_root->key < i_left && i_root->key < i_right)
        {
            i_root = i_root->right;
        }
        // found LCA
        else
        {
            break;
        }
    }

    // if both keys present return root
    if (search(i_root, i_left) != nullptr && search(i_root, i_right) != nullptr)
    {
        return i_root;
    }

    // at least one key is not present
    return nullptr;
}

/**
* @brief Finds in-order successor of given key.
* @tparam KeyType Type of keys in nodes.
* @param[in] i_root Root of BST.
* @param[in] i_key Value of key.
* @return In-order successor of given key.
*/
template<class KeyType>
TNode<KeyType> * inOrderSuccessor(TNode<KeyType> * i_root, const KeyType & i_key)
{
    // tree is empty
    if (i_root == nullptr)
    {
        return i_root;
    }

    // current successor
    TNode<KeyType> * succ = nullptr;
    // traverse tree
    while (i_root != nullptr)
    {
        if (i_root->key > i_key)
        {
            // store previous successor
            succ = i_root;
            // move to left subtree
            i_root = i_root->left;
        }
        else if (i_root->key < i_key)
        {
            // move to right subtree
            i_root = i_root->right;
        }
        // key found
        else
        {
            break;
        }
    }

    // if node has right child simply find minimum of left subtree
    if (i_root != nullptr && i_root->right != nullptr)
    {
        succ = minNode(i_root->right);
    }

    // key not found
    if (i_root == nullptr)
    {
        succ = nullptr;
    }

    return succ;
}

/**
 * @brief Finds k-th smallest element in BST (similar to in-order traversal).
 * @tparam KeyType Type of keys in nodes.
 * @param[in] i_root Root of BST.
 * @param[in] i_k Order of element.
 * @return Node with k-th smallest key or NULL if i_k greater then size of tree.
 */
template<class KeyType>
TNode<KeyType> * kthSmallest(TNode<KeyType> * i_root, std::size_t i_k)
{
    // auxiliary data structure
    std::stack<TNode<KeyType> *> st;

    TNode<KeyType> * node = nullptr;

    // always move left
    while (i_root)
    {
        // store node
        st.push(i_root);
        // move left
        i_root = i_root->left;
    }

    // precess tree nodes
    while (!st.empty())
    {
        // pop top item
        node = st.top();
        st.pop();

        // decrement counter
        i_k--;
        // check if poped node was k-th node
        if (i_k == 0)
        {
            break;
        }

        // move right
        if (node->right != nullptr)
        {
            node = node->right;
            // always move left
            while (node)
            {
                st.push(node);
                node = node->left;
            }
        }
    }

    // k is greater then size of tree
    if (st.empty())
    {
        return nullptr;
    }

    return node;
}

/**
* @brief Merges two BST.
* @tparam KeyType Type of keys in nodes.
* @tparam VisitFunc Type of unary function.
* @param[in] i_root1 Root of the first binary search tree.
* @param[in] i_root2 Root of the second binary search tree.
* @param[in] i_func Operation which will be applied to keys in nodes.
*/
template<class KeyType, class VisitFunc>
void merge2BSTUtil(TNode<KeyType> * i_root1, TNode<KeyType> * i_root2, VisitFunc i_func)
{
    // auxiliary data structures for inorder traversals
    std::stack<TNode<KeyType> *> s1, s2;

    // if first tree is empty process the second
    if (i_root1 == nullptr)
    {
        inorder(i_root2, i_func);
    }

    // if second tree is empty process the first
    if (i_root2 == nullptr)
    {
        inorder(i_root1, i_func);
    }

    TNode<KeyType> *curr1 = i_root1;
    TNode<KeyType> *curr2 = i_root2;

    // inorder traversal of both trees
    while (curr1 != nullptr || !s1.empty() || curr2 != nullptr || !s2.empty())
    {
        // always move left
        if (curr1 != nullptr || curr2 != nullptr)
        {
            // move left in first tree
            if (curr1 != nullptr)
            {
                s1.push(curr1);
                curr1 = curr1->left;
            }
            // move left in second tree
            if (curr2 != nullptr)
            {
                s2.push(curr2);
                curr2 = curr2->left;
            }
        }
        else
        {
            // all nodes in first tree are precessed
            if (s1.empty())
            {
                // process rest nodes in the second tree
                while (!s2.empty())
                {
                    // remove top most element
                    curr2 = s2.top();
                    s2.pop();
                    // unlink left subtree
                    curr2->left = nullptr;
                    // process rest nodes
                    inorder(curr2, i_func);
                }
                return;
            }

            // all nodes in second tree are precessed
            if (s2.empty())
            {
                // process rest nodes in the first tree
                while (!s1.empty())
                {
                    // remove top most element
                    curr1 = s1.top();
                    s1.pop();
                    // unlink left subtree
                    curr1->left = nullptr;
                    // process rest nodes
                    inorder(curr1, i_func);
                }
                return;
            }

            // pop top element from first tree
            curr1 = s1.top();
            s1.pop();

            // pop top element from second tree
            curr2 = s2.top();
            s2.pop();

            // similar to merge in merge sort
            if (curr1->key < curr2->key)
            {
                // process key
                i_func(curr1->key);
                // move to right subtree
                curr1 = curr1->right;
                // push back second node
                s2.push(curr2);
                curr2 = nullptr;
            }
            else
            {
                // process key
                i_func(curr2->key);
                // move to right subtree
                curr2 = curr2->right;
                // push back first node
                s1.push(curr1);
                curr1 = nullptr;
            }
        }
    }
}

/**
* @brief Finds ceil of given key.
* @tparam KeyType Type of keys in nodes.
* @param[in] i_root Root of BST.
* @param[in] i_key Value of key.
* @return Node with smallest key in BST which is greater than given key.
*/
template<class KeyType>
TNode<KeyType> * ceilBST(TNode<KeyType> * i_root, const KeyType & i_key)
{
    // tree is empty
    if (i_root == nullptr)
    {
        return i_root;
    }

    // found key
    if (i_root->key == i_key)
    {
        return i_root;
    }

    // ceil should be in right subtree
    if (i_key > i_root->key)
    {
        return ceilBST(i_root->right, i_key);
    }

    // ceil will key in root or key in left subtree
    TNode<KeyType> * node = ceilBST(i_root->left, i_key);
    if (node != nullptr)
    {
        if (node->key >= i_key)
        {
            return node;
        }
    }

    return i_root;
}

/**
* @brief Finds floor of given key.
* @tparam KeyType Type of keys in nodes.
* @param[in] i_root Root of BST.
* @param[in] i_key Value of key.
* @return Node with biggest key in BST which is smaller than given key.
*/
template<class KeyType>
TNode<KeyType> * floorBST(TNode<KeyType> * i_root, const KeyType & i_key)
{
    // tree is empty
    if (i_root == nullptr)
    {
        return i_root;
    }

    // found key
    if (i_root->key == i_key)
    {
        return i_root;
    }

    // floor should be in left subtree
    if (i_key < i_root->key)
    {
        return floorBST(i_root->left, i_key);
    }

    // ceil will key in root or key in right subtree
    TNode<KeyType> * node = floorBST(i_root->right, i_key);
    if (node != nullptr)
    {
        if (node->key <= i_key)
        {
            return node;
        }
    }

    return i_root;
}

/**
* @brief Implementation of Binary Search Tree.
* @tparam KeyType Type of keys in nodes.
*/
template<class KeyType>
class BinarySearchTree
{
public:
    /**
    * @brief Default constructor.
    */
    BinarySearchTree(TNode<KeyType> * i_root = nullptr)
        : m_root(i_root)
    {}

    /**
     * @brief Gets root of tree.
     * @return Root of binary search tree.
     */
    TNode<KeyType> * root() const
    {
        return m_root;
    }

    /**
    * @brief Performs pre-order binary tree traversal.
    * @tparam Visitor Type of unary function used from keys processing.
    * @param[in] i_func Unary function for processing keys in nodes.
    */
    template<class Visitor>
    void preorder(Visitor i_func) const
    {
        ::preorder(m_root, i_func);
    }

    /**
    * @brief Performs in-order binary tree traversal.
    * @tparam Visitor Type of unary function used from keys processing.
    * @param[in] i_func Unary function for processing keys in nodes.
    */
    template<class Visitor>
    void inorder(Visitor i_func) const
    {
        ::inorder(m_root, i_func);
    }

    /**
    * @brief Performs iterative in-order binary tree traversal.
    * @tparam Visitor Type of unary function used from keys processing.
    * @param[in] i_func Unary function for processing keys in nodes.
    */
    template<class Visitor>
    void inorder_iter(Visitor i_func) const
    {
        ::inorder_iter(m_root, i_func);
    }

    /**
    * @brief Performs post-order binary tree traversal.
    * @tparam Visitor Type of unary function used from keys processing.
    * @param[in] i_func Unary function for processing keys in nodes.
    */
    template<class Visitor>
    void postorder(Visitor i_func) const
    {
        ::postorder(m_root, i_func);
    }

    /**
    * @brief Performs level-order binary tree traversal (BFS).
    * @tparam Visitor Type of unary function used from keys processing.
    * @param[in] i_func Unary function for processing keys in nodes.
    */
    template<class Visitor>
    void levelorder(Visitor i_func) const
    {
        ::levelorder(m_root, i_func);
    }

    /**
    * @brief Performs binary tree traversal at k-th level.
    * @tparam Visitor Type of unary function used from keys processing.
    * @param[in] i_func Unary function for processing keys in nodes.
    * @param[in] i_level Distance from root.
    */
    template<class Visitor>
    void kth_level(Visitor i_func, std::size_t i_level) const
    {
        // get height of tree
        std::size_t h = ::height(m_root);
        if (h <= i_level)
        {
            return;
        }
        ::kthLevel(m_root, i_func, i_level);
    }

    /**
    * @brief Processes all ancestors of node with given key.
    * @tparam Visitor Type of unary function used from keys processing.
    * @param[in] i_func Unary function for processing keys in nodes.
    * @param[in] i_key Key to be searched.
    * @return True if key was found and False otherwise.
    */
    template<class Visitor>
    bool processAncestors(Visitor i_func, const KeyType & i_key)
    {
        return ::processAncestors(m_root, i_key, i_func);
    }

    /**
     * @brief Finds predecessor and successor of given key in in-order traversal of BST.
     * @param[in] i_key Value of key.
     * @return Pair of predecessor and successor of given key.
     */
    std::pair<TNode<KeyType> *, TNode<KeyType> *> find_pred_succ(const KeyType & i_key)
    {
        TNode<KeyType> *pred, *succ;
        // recursively find predecessor and successor
        ::findPredecessorAndSuccessor(m_root, &pred, &succ, i_key);

        return std::make_pair(pred, succ);
    }

    /**
    * @brief Calculates height of binary tree.
    * @return Height of binary tree.
    */
    std::size_t height() const
    {
        return ::height(m_root);
    }

    /**
    * @brief Calculates diameter of binary tree (maximum distance between two leafs).
    * @return Diameter of binary tree.
    */
    std::size_t diameter() const
    {
        return ::diameter(m_root);
    }

    /**
    * @brief Calculates width of binary tree.
    * @return Width of binary tree.
    */
    std::size_t width() const
    {
        return ::maxWidth(m_root);
    }

    /**
    * @brief Calculates width of binary tree.
    * @return Width of binary tree.
    */
    std::size_t width_optimized() const
    {
        return ::maxWidthOptimized(m_root);
    }

    /**
    * @brief Calculates diameter of binary tree (maximum distance between two leafs).
    * @return Diameter of binary tree.
    */
    std::size_t diameter_optimized() const
    {
        // inital height
        std::size_t height = 0U;
        return ::diameter_optimized(m_root, &height);
    }

    /**
    * @brief Inserts new key into BST.
    * @param[in] i_key Key to be added.
    */
    void insert(const KeyType & i_key)
    {
        ::insert(&m_root, i_key);
    }

    /**
     * @brief Searches key in BST.
     * @param[in] i_key Value of key to be searched.
     * @return Node with given key or NULL if key not found. 
     */
    TNode<KeyType> * search(const KeyType & i_key) const
    {
        return ::search(m_root, i_key);
    }

    /**
    * @brief Removes key from BST.
    * @param[in] i_key Key to be deleted.
    */
    void delete_key(const KeyType & i_key)
    {
        m_root = ::delete_node(&m_root, i_key);
    }

    /**
     * @brief Searches minimal value in non empty BST.
     * @return Minimum value in BST.
     */
    const KeyType & min_value() const
    {
        TNode<KeyType> * min_node = ::minNode(m_root);
        return min_node->key;
    }

    /**
    * @brief Clones binary tree.
    * @return Copy of binary tree.
    */
    BinarySearchTree clone() const
    {
        // copy tree
        TNode<KeyType> * root = ::clone(m_root);
        return BinarySearchTree(root);
    }

    /**
    * @brief Constructs binary tree from in-order and pre-order traversals.
    * @param[in] i_inorder In-order tree traversal.
    * @param[in] i_preorder Pre-order tree traversal.
    */
    void buildTreeInPreOrder(const std::vector<KeyType> & i_inorder, const std::vector<KeyType> & i_preorder)
    {
        // clear tree
        ::clear(&m_root);
        // construct new tree
        m_root = ::buildTreeInPreOrder(i_inorder, i_preorder, 0, i_inorder.size() - 1);
    }

    /**
    * @brief Checks wether tree is subtree of given tree.
    * @param[in] i_tree Binary tree.
    * @return True if tree is subtree of given tree and False otherwise.
    */
    bool is_subtree(const BinarySearchTree & i_tree)
    {
        return ::isSubtree(i_tree.m_root, m_root);
    }

    /**
     * @brief Recursively finds LCA of given keys.
     * @param[in] i_left First key.
     * @param[in] i_right Second key.
     * @return LCA of given keys if both present and NULL otherwise.
     */
    TNode<KeyType> * lca_recursive(const KeyType & i_left, const KeyType & i_right) const
    {
        return ::lcaRecur(m_root, i_left, i_right);
    }

    /**
    * @brief Iteratively finds LCA of given keys.
    * @param[in] i_left First key.
    * @param[in] i_right Second key.
    * @return LCA of given keys if both present and NULL otherwise.
    */
    TNode<KeyType> * lca_iterative(const KeyType & i_left, const KeyType & i_right) const
    {
        return ::lcaIter(m_root, i_left, i_right);
    }

    /**
     * @brief Finds node with key equals to in-order successor of given node.
     * @param[in] i_key Value of key.
     * @return Node with key equals to in-order successor or NULL if successor not found.
     */
    TNode<KeyType> * inorder_succ(const KeyType & i_key) const
    {
        return ::inOrderSuccessor(m_root, i_key);
    }

    /**
     * @brief Finds node with k-th smallest element in tree.
     * @param[in] i_k Order of node.
     * @return Node with k-th smallest element and NULL if order is greater then size of tree.
     */
    TNode<KeyType> * kth_smallest(const std::size_t i_k) const
    {
        return ::kthSmallest(m_root, i_k);
    }

    /**
     * @brief Finds ceil of given key.
     * @param[in] i_key Value of key.
     * @return Node with ceil if found and NULL if key is greater than given key.
     */
    TNode<KeyType> * ceil(const KeyType & i_key) const
    {
        return ::ceilBST(m_root, i_key);
    }

    /**
    * @brief Finds floor of given key.
    * @param[in] i_key Value of key.
    * @return Node with floor if found and NULL if key is smaller than given key.
    */
    TNode<KeyType> * floor(const KeyType & i_key) const
    {
        return ::floorBST(m_root, i_key);
    }

    /**
    * @brief Destructor.
    */
    ~BinarySearchTree()
    {
        ::clear(&m_root);
    }

private:
    TNode<KeyType> * m_root;            /**< Root of tree. */
};

/**
* @brief Merges two BST.
* @tparam KeyType Type of keys in nodes.
* @tparam VisitFunc Type of unary function.
* @param[in] i_bst1 First binary search tree.
* @param[in] i_bst2 Second binary search tree.
* @param[in] i_func Operation which will be applied to keys in nodes.
*/
template<class KeyType, class VisitFunc>
void merge2BST(const BinarySearchTree<KeyType> & i_bst1, const BinarySearchTree<KeyType> & i_bst2, VisitFunc i_func)
{
    merge2BSTUtil(i_bst1.root(), i_bst2.root(), i_func);
}
