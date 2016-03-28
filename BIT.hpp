#pragma once

#include <vector>

/**
 * @brief Binary Indexed Tree definition.
 */
class BinaryIndexedTree
{
public:
    /**
     * @brief Binary Indexed Tree constructor.
     * @param[in] i_arr Array of values.
     */
    BinaryIndexedTree(const std::vector<int> & i_arr);

    /**
     * @brief Gets sum of values from array in range 0..idx
     * @param[in] i_idx Right most index.
     * @return Sum of range.
     */
    int get_sum(int i_idx) const;

    /**
     * @brief Update value of array at given index.
     * @param[in] i_idx Index in array.
     * @param[in] i_val New value.
     */
    void update(int i_idx, int i_val);

private:
    std::vector<int> m_tree;    /**< Data stored in tree. */
    std::vector<int> m_orig;    /**< Original array.      */
};