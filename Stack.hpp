#pragma once

/**
 * @brief Definition of class Stack (implementation based on Singly Linked List).
 * @tparam ValueType Type of values stored in Stack.
 */
template<class ValueType>
class Stack
{
public:
    struct Node;                       /**< Forward declaration. */

    /**
     * Default constructor.
     */
    Stack()
        : m_head(nullptr)
    {}

    /**
     * @brief Adds an item in the stack.
     * @param[in] i_data Data to be stored in stack. 
     */
    void push(const ValueType & i_data)
    {
        // create new node
        Node * node = new Node;
        node->data = i_data;
        node->next = m_head;
        // change head if stack
        m_head = node;
    }

    /**
     * @brief Removes item from top of stack.
     */
    void pop()
    {
        // check if list is empty
        if (!empty())
        {
            Node * head = m_head;
            // move to next node
            m_head = m_head->next;
            // free memory
            delete head;
        } 
    }

    /**
     * @brief Get the topmost item.
     * @return Data stored in the topmost item.
     */
    const ValueType & top() const
    {
        return m_head->data;
    }

    /**
     * @brief Check wether stack is empty.
     * @return True if stack is empty and False otherwise.
     */
    bool empty() const
    {
        return m_head == nullptr;
    }

    /**
     * @brief Destructor.
     */
    ~Stack()
    {
        while (!empty())
        {
            pop();
        }
    }

private:
    /**
     * @brief Definition of one node of stack.
     */
    struct Node
    {
        ValueType data;       /**< Data stored in node.   */
        Node * next;          /**< Pointer to next node.  */
    };

    Node * m_head;            /**< Top of stack.          */
};
