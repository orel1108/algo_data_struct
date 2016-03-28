#pragma once

#include <algorithm>

#include "Stack.hpp"

/**
 * @brief Special stack data structure which performs push, pop and getMinimum in constant time.
 * The approach here is to use two stack, one contains actual data and other contains minimum values.
 * @tparam ValueType Type of values in stack.
 */
template<class ValueType>
class SpecialStack
{
public:

    /**
     * @brief Add item to actual stack and minimum of item and top of min stack to min stack.
     * @param[in] i_data Item to be stored.
     */
    void push(const ValueType & i_data)
    {
        // if stack is empty simply push item
        if (m_stack.empty())
        {
            m_stack.push(i_data);
            m_min.push(i_data);
        }
        else
        {
            // add data to stack
            m_stack.push(i_data);
            // add minimum of input value and top of stack wich holds minimum values
            m_min.push(std::min(i_data, m_min.top()));
        }
    }

    /**
     * @brief Gets topmost value from stack.
     * @return Topmost value from actual stack.
     */
    const ValueType & top() const
    {
        return m_stack.top();
    }

    /**
     * @brief Gets current minimum value on stack.
     * @return Current minimum value.
     */
    const ValueType & min() const
    {
        return m_min.top();
    }

    /**
     * @brief Pops topmost elements from two stacks.
     */
    void pop()
    {
        m_stack.pop();
        m_min.pop();
    }

    /**
     * @brief Check wether stack is empty.
     * @return True if stack is empty and False otherwise.
     */
    bool empty()
    {
        return m_stack.empty();
    }

private:
    Stack<ValueType> m_stack; /**< Store actual data.                */
    Stack<ValueType> m_min;   /**< Store minimum value on each step. */
};