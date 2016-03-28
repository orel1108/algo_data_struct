#pragma once

/**
 * @brief Double Ended Queue implementation based on Doubly Linked List.
 * @tparam ValueType Type of item in dequeue.
 */
template<class ValueType>
class Dequeue
{
public:
    struct Node;           /**< Forward declaration. */

    /**
     * @brief Default destructor.
     */
    Dequeue()
        : m_head(nullptr)
        , m_tail(nullptr)
    {}

    /**
     * @brief Checks if dequeue is empty.
     * @return True if dequeue is empty and False otherwise.
     */
    bool empty()
    {
        return m_head == nullptr;
    }

    /**
     * @brief Adds new value at the front of dequeue.
     * @param[in] i_key Key to be added.
     */
    void insert_front(const ValueType & i_key)
    {
        // create new node
        Node * node = new Node;
        node->key = i_key;
        node->prev = nullptr;
        node->next = nullptr;

        // if dequeue is empty, simply set head and tail to new node
        if (m_head == nullptr)
        {
            m_head = m_tail = node;
        }
        else
        {
            // create new link
            node->next = m_head;
            // create link to previous node
            m_head->prev = node;
            // change head
            m_head = node;
        }
    }

    /**
    * @brief Adds new value at the end of dequeue.
    * @param[in] i_key Key to be added.
    */
    void insert_last(const ValueType & i_key)
    {
        // create new node
        Node * node = new Node;
        node->key = i_key;
        node->prev = nullptr;
        node->next = nullptr;

        // if dequeue is empty, simply set head and tail to new node
        if (m_head == nullptr)
        {
            m_head = m_tail = node;
        }
        else
        {
            // create link to prevoius node
            node->prev = m_tail;
            // create new link
            m_tail->next = node;
            // change last node
            m_tail = node;
        }

    }

    /**
     * @brief Removes item from front of dequeue.
     */
    void delete_front()
    {
        // delete node if dequeue is not empty
        if (m_head != nullptr)
        {
            if (m_head->next == nullptr)
            {
                // free memory
                delete m_head;
                m_head = m_tail = nullptr;
            }
            else
            {
                Node * head = m_head;
                // remove link
                m_head->next->prev = nullptr;
                // move to next node
                m_head = m_head->next;

                // free memory
                delete head;
            }
        }
    }

    /**
    * @brief Removes item from end of dequeue.
    */
    void delete_last()
    {
        // check if dequeue is not empty
        if (m_tail != nullptr)
        {
            // dequeue contains only one node
            if (m_tail->prev == nullptr)
            {
                // free memory
                delete m_tail;
                m_head = m_tail = nullptr;
            }
            else
            {
                Node * tail = m_tail;
                // unlink last node
                m_tail->prev->next = nullptr;
                // move to previous node
                m_tail = m_tail->prev;

                // free memory
                delete tail;

            }
        }
    }

    /**
     * @brief Get key from the front of dequeue.
     * @return Topmost item.
     */
    const ValueType & front() const
    {
        if (m_head != nullptr)
        {
            return m_head->key;
        }
        exit(1);
    }

    /**
    * @brief Get key from the end of dequeue.
    * @return Lastmost item.
    */
    const ValueType & last() const
    {
        if (m_tail != nullptr)
        {
            return m_tail->key;
        }
        exit(1);
    }

    /**
     * @brief Destructor.
     */
    ~Dequeue()
    {
        // remove all elements
        while (!empty())
        {
            delete_front();
        }
    }

private:
    /**
     * Definition of dequeue node.
     */
    struct Node
    {
        ValueType key;         /**< Key stored in node.       */
        struct Node * prev;    /**< Pointer to previous node. */
        struct Node * next;    /**< Pointer to next node.     */
    };

    Node * m_head;            /**< First node.                */
    Node * m_tail;            /**< Last node.                 */
};