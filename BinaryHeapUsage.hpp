#pragma once

#include <vector>

#include "BinaryMinHeap.hpp"

/**
 * @brief Sorts nearly sorted array (each element is k away from its target position).
 * @param[in,out] io_buf Array to be sorted.
 * @param[in] i_k Distance to target position.
 */
template<class ValueType>
void sortNearlySorted(std::vector<ValueType> & io_buf, std::size_t i_k)
{
    const std::size_t n = io_buf.size();

    // auxiliary data structure
    MinHeap<ValueType> heap(i_k + 1);
    // insert first k + 1 keys
    for (std::size_t pos = 0U; pos <= i_k; pos++)
    {
        heap.insert_key(io_buf[pos]);
    }

    // on each step extract min from heap and add new key
    for (std::size_t pos = i_k + 1, curr = 0U; curr < n; pos++, curr++)
    {
        if (pos < n)
        {
            io_buf[curr] = heap.extract_min();
            heap.insert_key(io_buf[pos]);
        }
        else
        {
            io_buf[curr] = heap.extract_min();
        }
    }
}
