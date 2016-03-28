#pragma once

/**
 * @brief Queue implementation based on linked list.
 * @tparam ValueType Type of values stored in queue.
 */
template<class ValueType>
class Queue
{
public:
    struct QNode;     /**< Forward declaration. */

    /**
     * @brief Default constructor.
     */
    Queue()
        : m_front(nullptr)
        , m_rear(nullptr)
    {}

    /**
     * @brief Checks if queue is empty.
     * @return True if queue is empty and False otherwise.
     */
    bool empty() const
    {
        return m_front == nullptr;
    }

    /**
     * @brief Gets key from front node of queue.
     * @return Key stored in front node.
     */
    const ValueType & front() const
    {
        if (!empty())
        {
            return m_front->key;
        }
        // if queue is empty simply exit
        else
        {
            exit(1);
        }
    }

    /**
    * @brief Gets key from rear node of queue.
    * @return Key stored in rear node.
    */
    const ValueType & rear() const
    {
        if (!empty())
        {
            return m_rear->key;
        }
        // if queue is empty simply exit
        else
        {
            exit(1);
        }
    }

    /**
     * @brief Adds key to queue.
     * @param[in] i_key Key to be added to queue.
     */
    void enqueue(const ValueType & i_key)
    {
        // create new node
        QNode * node = new QNode;
        node->key = i_key;
        node->next = nullptr;

        // if queue is empty simple set front and rear node to new node
        if (empty())
        {
            m_front = m_rear = node;
        }
        else
        {
            // create link to next node
            m_rear->next = node;
            // change rear node
            m_rear = node;
        }
    }

    /**
     * @brief Removes element from queue.
     */
    void dequeue()
    {
        // if queue empty then nothing to do.
        if (empty())
        {
            return;
        }

        // copy front node
        QNode * node = m_front;

        // change front node
        m_front = m_front->next;

        // if queue becomes empty set rear node to NULL
        if (m_front == nullptr)
        {
            m_rear = nullptr;
        }

        // free memory
        delete node;
    }

    /**
     * @brief Destructor.
     */
    ~Queue()
    {
        // dequeue all elements.
        while (!empty())
        {
            dequeue();
        }
    }

private:
    /**
     * @brief Definiton of queue node.
     */
    struct QNode
    {
        ValueType key;            /**< Key stored in node.           */
        struct QNode * next;      /**< Pointer to next node.         */
    };

    QNode * m_front;             /**< Pointer to head of queue.      */
    QNode * m_rear;              /**< Pointer to last node in queue. */
};