#pragma once

#include <vector>

class RangeSumQuery
{
public:
    /**
     * @brief Constructs segment tree from given array.
     * @param[in] i_arr Input array.
     */
    void construct(const std::vector<int> & i_arr);

    /**
     * @brief Updates value in array at given position.
     * @param[in] i_pos Position in array.
     * @param[in] i_new_val New value.
     */
    void update(int i_pos, int i_new_val);

    /**
     * @brief Calculates sum of values from array in given range.
     * @param[in] i_left Left border.
     * @param[in] i_right Right border.
     * @return Sum of given range.
     */
    int get_sum(int i_left, int i_right);

private:
    std::vector<int> m_arr;           /**< Original array.    */
    std::vector<int> m_seg_tree;      /**< Segment tree data. */
    std::size_t m_size;               /**< Tree size.         */
};
