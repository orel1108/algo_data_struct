#include <cstddef>
#include <vector>
#include <algorithm>
#include <limits>

#include "RangeMinimumQuery.hpp"

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
        o_tree[i_idx] = std::min(construct_util(i_arr, o_tree, i_left, m, 2 * i_idx + 1),
            construct_util(i_arr, o_tree, m + 1, i_right, 2 * i_idx + 2));

        return o_tree[i_idx];
    }

    /**
    * @brief Calculates minimum of array values in given range.
    * @param[in] i_tree Segment tree.
    * @param[in] i_rleft Left most index of range.
    * @param[in] i_rright Right most index of range.
    * @param[in] i_left Left most index of query range.
    * @param[in] i_right Right most index of query range.
    * @param[in] i_idx Current index.
    * @return Minimum of array values in given range.
    */
    int get_min_util(std::vector<int> & i_tree, int i_rleft, int i_rright, int i_left, int i_right, int i_idx)
    {
        // check if segment of node is part of given range
        if (i_left <= i_rleft && i_rright <= i_right)
        {
            return i_tree[i_idx];
        }

        // segment don't overlap
        if (i_rright < i_left || i_rleft > i_right)
        {
            return std::numeric_limits<int>::max();
        }

        // get mid point
        int rm = mid(i_rleft, i_rright);

        // recursively get sum of nodes
        return std::min(get_min_util(i_tree, i_rleft, rm, i_left, i_right, 2 * i_idx + 1), get_min_util(i_tree, rm + 1, i_rright, i_left, i_right, 2 * i_idx + 2));
    }
}

/**
* @brief Constructs segment tree from given array.
* @param[in] i_arr Input array.
*/
void RangeMinimumQuery::construct(const std::vector<int> & i_arr)
{
    const std::size_t n = i_arr.size();

    // set size
    m_size = n;

    int tmp = static_cast<int>(ceil(std::log2(n)));

    // maximal size of segment tree
    const std::size_t max_size = 2 * static_cast<std::size_t>(std::pow(2, tmp)) - 1;

    m_seg_tree = std::vector<int>(max_size);

    // build tree
    construct_util(i_arr, m_seg_tree, 0, m_size - 1, 0);
}

/**
* @brief Calculates minimum of values from array in given range.
* @param[in] i_left Left border.
* @param[in] i_right Right border.
* @return Minimu of given range.
*/
int RangeMinimumQuery::get_min(int i_left, int i_right)
{
    if (i_left < 0 || i_right > static_cast<int>(m_size) - 1 || i_left > i_right)
    {
        return -1;
    }

    return get_min_util(m_seg_tree, 0, m_size - 1, i_left, i_right, 0);
}
