#pragma once

#include <cstdlib>

/**
 * @brief Class implements efficient solution for storing k stacks in single arrary.
 * @tparam ValueType Type of item in stack.
 */
template<class ValueType>
class kStacks
{
public:
    /**
     * @brief Constructor.
     * @param[in] i_n Size of array to store stacks.
     * @param[in] i_k Number of stacks.
     */
    kStacks(int i_n, int i_k)
    {
        m_data = new ValueType[i_n];

        m_top = new int[i_k];
        for (int pos = 0; pos < i_k; pos++)
        {
            // -1 indicates that stack is empty
            m_top[pos] = -1;
        }

        m_next = new int[i_n];
        for (int pos = 0; pos < i_n - 1; pos++)
        {
            // set next free to next position
            m_next[pos] = pos + 1;
        }
        // used to indicate that there are no free space
        m_next[i_n - 1] = -1;

        // set size
        m_n = i_n;
        // set number of stacks
        m_k = i_k;

        // set first free index
        m_free = 0;
    }

    /**
     * @brief Checks wether there are free space.
     * @return True if there are no free space and False otherwise.
     */
    bool full() const
    {
        return m_free == -1;
    }

    /**
     * @brief Check wether stack is empty.
     * @param[in] i_stack_num Stack number.
     * @return True if stack is empty and False otherwise.
     */
    bool empty(int i_stack_num) const
    {
        return m_top[i_stack_num] == -1;
    }

    /**
     * @brief Add new item to given stack.
     * @param[in] i_stack_num Stack number.
     * @param[in] i_data Item to be added
     */
    void push(int i_stack_num, const ValueType & i_data)
    {
        // check if array is full
        if (full())
        {
            return;
        }

        // store first free index
        const int idx = m_free;

        // update next free index
        m_free = m_next[idx];

        // store previous top index
        m_next[idx] = m_top[i_stack_num];
        // update top index
        m_top[i_stack_num] = idx;

        // store item
        m_data[idx] = i_data;
    }

    /**
     * @brief Gets topmost item from given stack.
     * @param[in] i_stack_num Stack number.
     * @return Topmost item from stack.
     */
    const ValueType & top(int i_stack_num) const
    {
        // check if stack is empty
        if (!empty(i_stack_num))
        {
            return m_data[m_top[i_stack_num]];
        }
        else
        {
            exit(1);
        }
    }

    /**
     * @brief Removes topmost item from given stack.
     * @param[in] i_stack_num Stack number.
     */
    void pop(int i_stack_num)
    {
        // check if stack is empty
        if (!empty(i_stack_num))
        {
            // get top index
            const int idx = m_top[i_stack_num];

            // change top index
            m_top[i_stack_num] = m_next[idx];

            // set index as free
            m_next[idx] = m_free;
            m_free = idx;
        }
    }

    /**
     * @brief Destructor.
     */
    ~kStacks()
    {
        delete[] m_data;
        delete[] m_top;
        delete[] m_next;
    }

private:
    ValueType * m_data;   /**< Content of k stacks.                        */

    int * m_top;          /**< Stores index of top element for each stack. */
    int * m_next;         /**< Stores free list.                           */

    int m_n;              /**< Size of stack.                              */
    int m_k;              /**< Number of stacks.                           */

    int m_free;           /**< First index of free list.                   */
};