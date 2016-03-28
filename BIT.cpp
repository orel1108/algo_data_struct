#include <vector>

#include "BIT.hpp"

namespace
{
    /**
     * @brief Utility function, updates value in array.
     */
    void update_util(std::vector<int> & io_tree, int i_n, int i_idx, int i_val)
    {
        i_idx++;
        while (i_idx <= i_n)
        {
            // add value to node
            io_tree[i_idx] += i_val;
            // move to child node
            i_idx += i_idx & (-i_idx);
        }
    }
}

/**
* @brief Binary Indexed Tree constructor.
* @param[in] i_arr Array of values.
*/
BinaryIndexedTree::BinaryIndexedTree(const std::vector<int> & i_arr)
{
    const int n = i_arr.size();
    // allocate memory for tree
    m_tree = std::vector<int>(n + 1);

    // add all values from array
    for (int pos = 0; pos < n; pos++)
    {
        update_util(m_tree, n, pos, i_arr[pos]);
    }

    // save original array
    m_orig = i_arr;
}

/**
* @brief Gets sum of values from array in range 0..idx
* @param[in] i_idx Right most index.
* @return Sum of range.
*/
int BinaryIndexedTree::get_sum(int i_idx) const
{
    int s = 0;
    i_idx++;
    // traverse from child
    while (i_idx > 0)
    {
        // add to sum
        s += m_tree[i_idx];
        // move to parent
        i_idx -= i_idx & (-i_idx);
    }

    return s;
}

/**
* @brief Update value of array at given index.
* @param[in] i_idx Index in array.
* @param[in] i_val New value.
*/
void BinaryIndexedTree::update(int i_idx, int i_val)
{
    const int n = m_orig.size();
    // get old value
    int old = m_orig[i_idx];

    // difference to be added
    int diff = i_val - old;
    // update value in original array
    m_orig[i_idx] = i_val;

    // update all nodes
    update_util(m_tree, n, i_idx, diff);
}
