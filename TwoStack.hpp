#pragma once

#include <cstdlib>
#include <limits>

/**
 * @brief Implementation of two stacks using single array.
 * @tparam ValueType Type of values stored in stacks.
 */
template<class ValueType>
class TwoStacks
{
public:
    /**
     * @brief Two stacks constructor.
     * @param[in] i_size Size of stack.
     */
    explicit TwoStacks(int i_size)
    {
        // allocate memory for stack
        m_data = new ValueType[i_size];
        m_size = i_size;
        // set top positions
        m_top1 = -1;
        m_top2 = i_size;
    }

    /**
     * @brief Adds element to the first stack.
     * @param[in] i_data Data to be pushed onto stack.
     */
    void push1(const ValueType & i_data)
    {
        // check if stacks do not overlap
        if (m_top1 < m_top2 - 1)
        {
            m_data[++m_top1] = i_data;
        }
    }

    /**
    * @brief Adds element to the second stack.
    * @param[in] i_data Data to be pushed onto stack.
    */
    void push2(const ValueType & i_data)
    {
        // check if stacks do not overlap
        if (m_top1 < m_top2 - 1)
        {
            m_data[--m_top2] = i_data;
        }
    }

    /**
     * @brief Extracts topmost item from first stack.
     * @return Topmost item in first stack.
     */
    const ValueType & top1() const
    {
        // check if first stack is not empty
        if (m_top1 >= 0)
        {
            return m_data[m_top1];
        }

        // stack is empty
        exit(1);
    }

    /**
    * @brief Extracts topmost item from second stack.
    * @return Topmost item in second stack.
    */
    const ValueType & top2() const
    {
        // check if second stack is not empty
        if (m_top2 < m_size)
        {
            return m_data[m_top2];
        }

        // stack is empty
        exit(1);
    }

    /**
     * @brief Removes topmost item from the first stack.
     */
    void pop1()
    {
        // check if first stack is not empty
        if (m_top1 >= 0)
        {
            m_top1--;
        }
    }

    /**
    * @brief Removes topmost item from the second stack.
    */
    void pop2()
    {
        // check if second stack is not empty
        if (m_top2 < m_size)
        {
            m_top2++;
        }
    }

    /**
     * @brief Destructor.
     */
    ~TwoStacks()
    {
        // free memory
        delete[] m_data;
    }

private:
    ValueType * m_data;    /**< Data stored in stack.     */
    int m_size;            /**< Size of stack.            */
    int m_top1, m_top2;    /**< Top positions of stacks.  */
};