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
 * @brief Checks wether binary tree is binary search tree.
 * @tparam KeyType Type of keys in nodes.
 * @param[in] i_root Root of binary tree.
 * @return True if tree is BST and False otherwise.
 */
template<class KeyType>
bool isBST(TNode<KeyType> * i_root)
{
    // store previously visited node
    static TNode<KeyType> * prev = nullptr;

    // preform in-order traversal
    if (i_root != nullptr)
    {
        // check left subtree
        if (!isBST(i_root->left))
        {
            return false;
        }

        // checks if values in in-order traversal are sorted
        if (prev != nullptr && i_root->key <= prev->key)
        {
            return false;
        }

        prev = i_root;

        // move to right subtree
        return isBST(i_root->right);
    }

    return true;
}

/**
 * @brief Finds path from to root node to node with given key.
 * @tparam KeyType Type of keys in nodes.
 * @param[in] i_root Root of binary tree.
 * @param[out] o_path Path from root to node.
 * @param[in] i_key Key to be searched.
 * @return True if path exist and False otherwise.
 */
template<class KeyType>
bool findPathFromRoot(TNode<KeyType> * i_root, std::vector<TNode<KeyType> *> & o_path, const KeyType i_key)
{
    // tree is empty
    if (i_root == nullptr)
    {
        return false;
    }

    // add current key, if it not in path then later it will be removed
    o_path.push_back(i_root);

    // found path to given node
    if (i_root->key == i_key)
    {
        return true;
    }

    // search path in left and right subtrees
    if ((i_root->left != nullptr && findPathFromRoot(i_root->left, o_path, i_key)) || (i_root->right != nullptr && findPathFromRoot(i_root->right, o_path, i_key)))
    {
        return true;
    }

    // remove added node
    o_path.pop_back();
    return false;
}

/**
 * @brief Finds Lowest common ancestor of two nodes with given keys.
 * @tparam KeyType Type of keys in nodes.
 * @param[in] i_root Root of binary tree.
 * @param[in] i_left First key.
 * @param[in] i_right Right key.
 * @return LCA if two keys in binary tree and NULL if at least one of keys is not present.
 */
template<class KeyType>
TNode<KeyType> * lcaNaive(TNode<KeyType> * i_root, const KeyType & i_left, const KeyType & i_right)
{
    // empty tree
    if (i_root == nullptr)
    {
        return i_root;
    }

    // paths to first and second nodes
    std::vector<TNode<KeyType> *> path1, path2;

    // find path to nodes, if one of keys is not present return NULL
    if (!findPathFromRoot(i_root, path1, i_left) || !findPathFromRoot(i_root, path2, i_right))
    {
        return nullptr;
    }

    // find first mismatch
    std::size_t pos = 0;
    for (; pos < std::min(path1.size(), path2.size()); pos++)
    {
        if (path1[pos]->key != path2[pos]->key)
        {
            break;
        }
    }

    return path1[pos - 1];
}

/**
 * @brief Checks if given key is present in tree.
 * @tparam KeyType Type of keys in nodes.
 * @param[in] i_root Root of binary tree.
 * @param[in] i_key Key to be searched.
 * @return True if key present in binary tree and False otherwise.
 */
template<class KeyType>
bool hasKey(TNode<KeyType> * i_root, const KeyType & i_key)
{
    // tree is empty
    if (i_root == nullptr)
    {
        return false;
    }

    return (i_root->key == i_key) || hasKey(i_root->left, i_key) || hasKey(i_root->right, i_key);
}

/**
* @brief Helper function for finding Lowest Common Ancestor of two nodes with given keys.
* @tparam KeyType Type of keys in nodes.
* @param[in] i_root Root of binary tree.
* @param[in] i_left First key.
* @param[in] i_right Right key.
* @param[out] o_e1 Indicates wether first key is present.
* @param[out] o_e2 Indicates wether second key is present.
* @return LCA if two keys in binary tree and NULL if at least one of keys is not present.
*/
template<class KeyType>
TNode<KeyType> * lcaRecurUtil(TNode<KeyType> * i_root, const KeyType & i_left, const KeyType & i_right, bool & o_e1, bool & o_e2)
{
    // tree is empty
    if (i_root == nullptr)
    {
        return nullptr;
    }

    // check if one of keys is in root node
    if (i_root->key == i_left)
    {
        o_e1 = true;
        return i_root;
    }
    if (i_root->key == i_right)
    {
        o_e2 = true;
        return i_root;
    }

    // search keys in left subtree
    TNode<KeyType> * left = lcaRecurUtil(i_root->left, i_left, i_right, o_e1, o_e2);
    // search keys in right subtree
    TNode<KeyType> * right = lcaRecurUtil(i_root->right, i_left, i_right, o_e1, o_e2);

    // one of key is in left subtree and other in right subtree
    if (left != nullptr && right != nullptr)
    {
        return i_root;
    }

    // LCA in left subtree
    if (left != nullptr)
    {
        return left;
    }

    // LCA in right subtree
    return right;
}

/**
* @brief Finds Lowest common ancestor of two nodes with given keys.
* @tparam KeyType Type of keys in nodes.
* @param[in] i_root Root of binary tree.
* @param[in] i_left First key.
* @param[in] i_right Right key.
* @return LCA if two keys in binary tree and NULL if at least one of keys is not present.
*/
template<class KeyType>
TNode<KeyType> * lca(TNode<KeyType> * i_root, const KeyType & i_left, const KeyType & i_right)
{
    bool e1 = false, e2 = false;
    // find LCA
    TNode<KeyType> * node = lcaRecurUtil(i_root, i_left, i_right, e1, e2);

    // if both keys are present
    if ((e1 && e2) || (e1 && hasKey(node, i_right)) || (e2 && hasKey(node, i_left)))
    {
        return node;
    }

    return nullptr;
}

/**
 * @brief Implementation of binary tree.
 * @tparam KeyType Type of keys in nodes.
 */
template<class KeyType>
class BinaryTree
{
public:
    /**
     * @brief Default constructor.
     */
    BinaryTree(TNode<KeyType> * i_root = nullptr)
        : m_root(i_root)
    {}

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
     * @brief Checks wether binary tree is binary search tree.
     * @return True if tree is BST and False otherwise.
     */
    bool is_bst() const
    {
        return ::isBST(m_root);
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
     * @brief Inserts new key into binary tree.
     * @param[in] i_key Key to be added.
     */
    void insert(const KeyType & i_key)
    {
        ::insert(&m_root, i_key);
    }

    /**
     * @brief Clones binary tree.
     * @return Copy of binary tree.
     */
    BinaryTree clone() const
    {
        // copy tree
        TNode<KeyType> * root = ::clone(m_root);
        return BinaryTree(root);
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
    bool is_subtree(const BinaryTree & i_tree)
    {
        return ::isSubtree(i_tree.m_root, m_root);
    }

    /**
     * @brief Finds path from root to node with given key.
     * @param[in] i_key Key to be searched.
     * @return True and path if path exists and False otherwise.
     */
    std::pair<bool, std::vector<TNode<KeyType> *>> path_from_root(const KeyType & i_key) const
    {
        // resulting path
        std::vector<TNode<KeyType> *> path;
        // search path
        bool exists = ::findPathFromRoot(m_root, path, i_key);

        return std::make_pair(exists, path);
    }

    /**
     * @brief Finds LCA of two nodes with given keys.
     * @param[in] i_left First key.
     * @param[in] i_right Second key.
     * @return LCA node if both keys present and NULL otherwise.
     */
    TNode<KeyType> * lca_naive(const KeyType & i_left, const KeyType & i_right)
    {
        return ::lcaNaive(m_root, i_left, i_right);
    }

    /**
    * @brief Finds LCA of two nodes with given keys.
    * @param[in] i_left First key.
    * @param[in] i_right Second key.
    * @return LCA node if both keys present and NULL otherwise.
    */
    TNode<KeyType> * lca(const KeyType & i_left, const KeyType & i_right)
    {
        return ::lca(m_root, i_left, i_right);
    }

    /**
     * @brief Destructor.
     */
    ~BinaryTree()
    {
        ::clear(&m_root);
    }

private:
    TNode<KeyType> * m_root;            /**< Root of tree. */
};
