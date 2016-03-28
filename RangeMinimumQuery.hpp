#pragma once

#include <cstddef>
#include <vector>

class RangeMinimumQuery
{
public:
    /**
    * @brief Constructs segment tree from given array.
    * @param[in] i_arr Input array.
    */
    void construct(const std::vector<int> & i_arr);

    /**
    * @brief Calculates minimum of values from array in given range.
    * @param[in] i_left Left border.
    * @param[in] i_right Right border.
    * @return Minimum of given range.
    */
    int get_min(int i_left, int i_right);

private:
    std::vector<int> m_seg_tree;      /**< Segment tree data. */
    std::size_t m_size;               /**< Tree size.         */
};
