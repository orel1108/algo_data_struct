#pragma once

#include <vector>
#include <algorithm>

/**
 * @brief Recursively heapifies array.
 * @param[in,out] io_buf Array to heapified.
 * @param[in] i_idx Index of root.
 * @param[in] i_size Current heap size.
 */
template<class ValueType>
void maxHeapify(std::vector<ValueType> & io_buf, std::size_t i_idx, std::size_t i_size)
{
    const std::size_t l_idx = 2 * i_idx + 1;
    const std::size_t r_idx = 2 * i_idx + 2;

    std::size_t largest = i_idx;
    if (l_idx < i_size && io_buf[l_idx] > io_buf[largest])
    {
        largest = l_idx;
    }
    if (r_idx < i_size && io_buf[r_idx] > io_buf[largest])
    {
        largest = r_idx;
    }

    if (largest != i_idx)
    {
        std::swap(io_buf[largest], io_buf[i_idx]);
        maxHeapify(io_buf, largest, i_size);
    }
}

/**
 * @brief Constructs max binary heap from given array.
 * @param[in,out] Array to be heapified.
 */
template<class ValueType>
void buildHeap(std::vector<ValueType> & io_buf)
{
    const std::size_t n = io_buf.size();
    for (int pos = n / 2; pos >= 0; pos--)
    {
        maxHeapify(io_buf, pos, n);
    }
}

/**
 * @brief Sorts array using heap sort algorithm.
 * @param[in,out] io_buf Array to be sorted.
 * @param[in] i_size Size of array.
 */
template<class ValueType>
void heapSort(std::vector<ValueType> & io_buf, std::size_t i_size)
{
    // construct heap
    buildHeap(io_buf);

    while (i_size > 1)
    {
        // set current max element to correct place
        std::swap(io_buf[0], io_buf[i_size - 1]);
        //decrease size of heap
        i_size--;
        // fix heap
        maxHeapify(io_buf, 0, i_size);
    }
}
