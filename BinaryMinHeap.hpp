#pragma once

#include <cstddef>
#include <algorithm>

/**
 * @brief Minimum Binary Heap implementation.
 * @tparam KeyType Type of keys stored in binary heap.
 */
template<class KeyType>
class MinHeap
{
public:
    /**
     * @brief Minimum heap constructor.
     * @param[in] i_capacity Capacity of heap.
     */
    MinHeap(const std::size_t i_capacity)
    {
        // allocate memory for heap
        m_heap = new KeyType[i_capacity];
        m_capacity = i_capacity;
        // currently heap is empty
        m_size = 0U;
    }

    /**
     * @brief Finds parent of given child.
     * @param[in] i_child Index of child.
     * @return Index of parent.
     */
    static std::size_t parent(const std::size_t i_child)
    {
        if (i_child > 0U)
        {
            return (i_child - 1) / 2;
        }
        return 0U;
    }

    /**
     * @brief Finds left child of given parent.
     * @param[in] i_parent Index of parent.
     * @return Index of left child.
     */
    static std::size_t left(const std::size_t i_parent)
    {
        return 2 * i_parent + 1;
    }

    /**
    * @brief Finds right child of given parent.
    * @param[in] i_parent Index of parent.
    * @return Index of right child.
    */
    static std::size_t right(const std::size_t i_parent)
    {
        return 2 * i_parent + 2;
    }

    /**
    * @brief Heapify subtree with given index.
    * @param[in] i_idx Input index.
    */
    void heapify(std::size_t i_idx)
    {
        // left child
        const std::size_t l_idx = left(i_idx);
        // right child
        const std::size_t r_idx = right(i_idx);

        // contains index of smallest key
        std::size_t smallest = i_idx;

        if (l_idx < m_size && m_heap[l_idx] < m_heap[smallest])
        {
            smallest = l_idx;
        }
        if (r_idx < m_size && m_heap[r_idx] < m_heap[smallest])
        {
            smallest = r_idx;
        }

        // if smallest in root then nothing to do
        if (smallest != i_idx)
        {
            // swap root with child
            std::swap(m_heap[i_idx], m_heap[smallest]);
            // recursively call for child
            heapify(smallest);
        }
    }

    /**
     * @brief Adds new key to heap.
     * @param[in] i_key Key to be added.
     */
    void insert_key(const KeyType & i_key)
    {
        // check if there are free space
        if (m_size < m_capacity)
        {
            // store key and increase sheap size
            m_heap[m_size++] = i_key;

            std::size_t idx = m_size - 1;
            // fix heap property
            while (idx > 0U && m_heap[parent(idx)] > m_heap[idx])
            {
                // swap parent and child
                std::swap(m_heap[idx], m_heap[parent(idx)]);
                idx = parent(idx);
            }
        }
    }

    /**
     * @brief Removes key at given position.
     * @param[in] i_idx Key index.
     */
    void delete_key(const std::size_t i_idx)
    {

    }

    /**
     * @brief Gets minimum element in heap.
     * @return Value stored in root.
     */
    KeyType get_min() const
    {
        return m_heap[0];
    }

    /**
     * @brief Removes minimum value from heap.
     * @return Removed key.
     */
    KeyType extract_min()
    {
        // heap contains only one element
        if (m_size == 1U)
        {
            m_size = 0U;
            return m_heap[0];
        }

        // store resulting value
        KeyType res = m_heap[0];
        // copy last element
        m_heap[0] = m_heap[m_size - 1];
        // decrease size of heap
        m_size--;

        // move key from root to correct place
        heapify(0U);

        return res;
    }

    /**
     * @brief Decreases key stored at given index.
     * @param[in] i_idx Index of node.
     * @param[in] i_key New key (should be less than current key).
     */
    void decrease_key(std::size_t i_idx, const KeyType & i_key)
    {
        // store new key
        m_heap[i_idx] = i_key;

        // swap child key with parent key until parent key is greater (keep heap property)
        while (i_idx > 0U && m_heap[parent(i_idx)] > m_heap[i_idx])
        {
            std::swap(m_heap[i_idx], m_heap[parent(i_idx)]);
            i_idx = parent(i_idx);
        }
    }

    /**
     * @brief Destructor.
     */
    ~MinHeap()
    {
        delete [] m_heap;
    }

private:
    KeyType*     m_heap;        /**< Binary heap data.   */
    std::size_t  m_capacity;    /**< Capacity of heap.   */
    std::size_t  m_size;        /**< Size of heap.       */
};
