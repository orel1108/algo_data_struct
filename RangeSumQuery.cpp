#include <vector>
#include <cmath>

#include "RangeSumQuery.hpp"

namespace
{
    /**
     * @brief Find middle point. 
     */
    int mid(int i_left, int i_right)
    {
        return i_left + (i_right - i_left) / 2;
    }

    /**
     * @brief Helper function for Segment tree construction.
     * @param[in] i_arr Input array.
     * @param[out] o_tree Resulting tree.
     * @param[in] i_left Left most index.
     * @param[in] i_right Right most index.
     * @param[in] i_idx Current index.
     */
    int construct_util(const std::vector<int> & i_arr, std::vector<int> & o_tree, int i_left, int i_right, int i_idx)
    {
        if (i_left == i_right)
        {
            o_tree[i_idx] = i_arr[i_left];
            return o_tree[i_idx];
        }

        // find middle index
        int m = mid(i_left, i_right);

        // find sum of children nodes
        o_tree[i_idx] = construct_util(i_arr, o_tree, i_left, m, 2 * i_idx + 1) +
            construct_util(i_arr, o_tree, m + 1, i_right, 2 * i_idx + 2);

        return o_tree[i_idx];
    }

    /**
     * @brief Updates values in nodes of segment tree.
     * @param[out] o_tree Resulting tree.
     * @param[in] i_left Left most index.
     * @param[in] i_right Right most index.
     * @param[in] i_pos Position in array to be updated.
     * @param[in] i_diff Value to be added to node values.
     * @param[in] i_idx Current index.
     */
    void update_util(std::vector<int> & o_tree, int i_left, int i_right, int i_pos, int i_diff, int i_idx)
    {
        // out of range
        if (i_pos < i_left || i_pos > i_right)
        {
            return;
        }

        o_tree[i_idx] += i_diff;
        if (i_left != i_right)
        {
            // get mid point
            int m = mid(i_left, i_right);
            // update nodes in left subtree
            update_util(o_tree, i_left, m, i_pos, i_diff, 2 * i_idx + 1);
            // update nodes in right subtree
            update_util(o_tree, m + 1, i_right, i_pos, i_diff, 2 * i_idx + 2);
        }
    }

    /**
     * @brief Calculates sum of array values in given range.
     * @param[in] i_tree Segment tree.
     * @param[in] i_rleft Left most index of range.
     * @param[in] i_rright Right most index of range.
     * @param[in] i_left Left most index of query range.
     * @param[in] i_right Right most index of query range.
     * @param[in] i_idx Current index.
     * @return Sum of array values in given range.
     */
    int get_sum_util(std::vector<int> & i_tree, int i_rleft, int i_rright, int i_left, int i_right, int i_idx)
    {
        // check if segment of node is part of given range
        if (i_left <= i_rleft && i_rright <= i_right)
        {
            return i_tree[i_idx];
        }

        // segment don't overlap
        if (i_rright < i_left || i_rleft > i_right)
        {
            return 0;
        }

        // get mid point
        int rm = mid(i_rleft, i_rright);

        // recursively get sum of nodes
        return get_sum_util(i_tree, i_rleft, rm, i_left, i_right, 2 * i_idx + 1) + get_sum_util(i_tree, rm + 1, i_rright, i_left, i_right, 2 * i_idx + 2);
    }
}

/**
* @brief Constructs segment tree from given array.
* @param[in] i_arr Input array.
*/
void RangeSumQuery::construct(const std::vector<int> & i_arr)
{
    const std::size_t n = i_arr.size();

    // copy original array
    m_arr = i_arr;
    // set size
    m_size = n;

    int tmp = static_cast<int>(ceil(std::log2(n)));

    // maximal size of segment tree
    const std::size_t max_size = 2 * static_cast<std::size_t>(std::pow(2, tmp)) - 1;

    m_seg_tree = std::vector<int>(max_size);

    // build tree
    construct_util(m_arr, m_seg_tree, 0, m_size - 1, 0);
}

/**
* @brief Updates value in array at given position.
* @param[in] i_pos Position in array.
* @param[in] i_new_val New value.
*/
void RangeSumQuery::update(int i_pos, int i_new_val)
{
    // check index range
    if (i_pos < 0 || i_pos > static_cast<int>(m_size) - 1)
    {
        return;
    }

    // get value to be added
    int diff = i_new_val - m_arr[i_pos];

    // update value in original array
    m_arr[i_pos] = i_new_val;

    // update values in tree
    update_util(m_seg_tree, 0, m_size - 1, i_pos, diff, 0);
}

/**
* @brief Calculates sum of values from array in given range.
* @param[in] i_left Left border.
* @param[in] i_right Right border.
* @return Sum of given range.
*/
int RangeSumQuery::get_sum(int i_left, int i_right)
{
    if (i_left < 0 || i_right > static_cast<int>(m_size) - 1 || i_left > i_right)
    {
        return -1;
    }

    return get_sum_util(m_seg_tree, 0, m_size - 1, i_left, i_right, 0);
}
