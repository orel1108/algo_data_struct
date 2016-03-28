#pragma once

#include <iostream> 

/**
 * @brief Implementation of Singly Linked List.
 * @tparam ValueType Type of item stored in list.
 */
template<class ValueType>
class SinglyLinkedList
{
public:
    struct Node;                     /**< Forward declaration. */

    /**
     * @brief Default constructor.
     */
    SinglyLinkedList()
        : m_head(nullptr)
    {}

    /**
     * @brief Gets head of list.
     */
    Node * head() const
    {
        return m_head;
    }

    /**
     * @brief Insert new node on the front of the list.
     * @param[in] i_data Data of new node.
     */
    void push_front(const ValueType & i_data)
    {
        // create new node
        Node * new_head = new Node;
        // store data
        new_head->data = i_data;
        // add reference
        new_head->next = m_head;
        // change head of list
        m_head = new_head;
    }

    /**
    * @brief Insert new node at the end of the list.
    * @param[in] i_data Data of new node.
    */
    void push_back(const ValueType & i_data)
    {
        // create new node
        Node * new_node = new Node;
        // store data
        new_node->data = i_data;
        // set next pointer to NULL pointer
        new_node->next = nullptr;

        // check if head of list is NULL
        if (m_head == nullptr)
        {
            m_head = new_node;
        }
        // otherwise go to the end of list
        else
        {
            Node * head = m_head;
            while (head->next != nullptr)
            {
                head = head->next;
            }
            head->next = new_node;
        }
    }

    /**
     * @brief Removes node from the front of the list.
     */
    void pop_front()
    {
        // check if list is not empty
        if (m_head != nullptr)
        {
            // store head
            Node * head = m_head;
            // move to next node
            m_head = head->next;
            // free memory
            delete head;
        }
    }

    /**
    * @brief Removes node from the end of the list.
    */
    void pop_back()
    {
        // check if list is not empty
        if (m_head != nullptr)
        {
            // store head of the list
            Node * head = m_head;
            // check if the list contains at least two nodes
            if (head->next != nullptr)
            {
                Node * prev = nullptr;
                // move to the end of the list
                while (head->next != nullptr)
                {
                    prev = head;
                    head = head->next;
                }
                // unlink last node
                prev->next = nullptr;
                // free memory
                delete head;
            }
            else
            {
                // delete head node
                m_head = nullptr;
                delete head;
            }
        }
    }

    /**
     * @brief Removes node from list with specified key.
     * @param[in] i_key Value of key.
     */
    void delete_node(const ValueType & i_key)
    {
        Node *head, *prev;
        // copy head node
        head = m_head;
        prev = nullptr;

        // check if head contains key
        if (head != nullptr && head->data == i_key)
        {
            // reset head
            m_head = head->next;
            // free memory
            delete head;
        }
        else
        {
            // search key
            while (head != nullptr && head->data != i_key)
            {
                // store previously visited node
                prev = head;
                head = head->next;
            }
            // key not found
            if (head == nullptr)
            {
                return;
            }
            else
            {
                // unlink node
                prev->next = head->next;
                // free memory
                delete head;
            }
        }
    }

    /**
     * @brief Swaps two nodes in the list.
     * @param[in] i_left Value stored in the left node.
     * @param[in] i_right Value stored in the right node.
     */
    void swap_nodes(const ValueType & i_left, const ValueType & i_right)
    {
        // nothing to swap (same nodes)
        if (i_left == i_right)
        {
            return;
        }

        Node *prevLeft = nullptr, *currLeft = m_head;
        // lookup node with key equals to left value
        while (currLeft != nullptr && currLeft->data != i_left)
        {
            // store previously visited node
            prevLeft = currLeft;
            // go to the next node
            currLeft = currLeft->next;
        }

        Node *prevRight = nullptr, *currRight = m_head;
        // lookup node with key equals to right value
        while (currRight != nullptr && currRight->data != i_right)
        {
            // store previously visited node
            prevRight = currRight;
            // go to the next node
            currRight = currRight->next;
        }

        // case if either left or right value not present
        if (currLeft == nullptr || currRight == nullptr)
        {
            return;
        }

        // check if left value not in the head of the list
        if (prevLeft != nullptr)
        {
            prevLeft->next = currRight;
        }
        // else make new head
        else
        {
            m_head = currRight;
        }

        // check if right value not in the head of the list
        if (prevRight != nullptr)
        {
            prevRight->next = currLeft;
        }
        // else make new head
        else
        {
            m_head = currLeft;
        }

        // swap next nodes
        Node * temp = currRight->next;
        currRight->next = currLeft->next;
        currLeft->next = temp;
    }

    /**
     * @brief Iteratively reverse the list.
     */
    void reverse_iterative()
    {
        Node *prev = nullptr, *curr = m_head, *next = nullptr;
        // change next to prev, prev to curr and curr to next
        while (curr != nullptr)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        // reset head of the list
        m_head = prev;
    }

    /**
     * @brief Recursively reverse the list. 
     */
    void reverse_recursive()
    {
        // call private recursive reversion.
        p_reverse_recursive(&m_head);
    }

    /**
     * @brief Reverse list in groups of given size.
     * @param[in] i_k Size of group.
     */
    void reverse_in_blocks(const std::size_t i_k)
    {
        m_head = p_reverse_block(m_head, i_k);
    }

    /**
     * @brief Detects cycle in the list.
     * @return True if cycle is found and False otherwise.
     */
    bool detect_cycle() const
    {
        Node *slow_ptr = m_head, *fast_prt = m_head;
        while (slow_ptr != nullptr && fast_prt != nullptr && fast_prt->next != nullptr)
        {
            // move by one node
            slow_ptr = slow_ptr->next;
            // move by two nodes
            fast_prt = fast_prt->next->next;
            if (slow_ptr == fast_prt)
            {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Detect and removes cycle from list.
     */
    void detect_and_remove_cycle()
    {
        Node *slow_ptr = m_head, *fast_ptr = m_head->next;
        while (fast_ptr != nullptr && fast_ptr->next != nullptr)
        {
            // found cycle
            if (slow_ptr == fast_ptr)
            {
                break;
            }
            // move by one node
            slow_ptr = slow_ptr->next;
            // move by two nodes
            fast_ptr = fast_ptr->next->next;
        }

        // remove cycle
        if (slow_ptr == fast_ptr)
        {
            slow_ptr = m_head;
            // move by one node
            while (slow_ptr != fast_ptr->next)
            {
                slow_ptr = slow_ptr->next;
                fast_ptr = fast_ptr->next;
            }
            // remove link
            fast_ptr->next = nullptr;
        }
    }

    /**
     * @brief Rotates the list counter-clockwise.
     * @param[in] i_k Rotation step (should be less the size of the list).
     */
    void rotate_counter_clockwise(const std::size_t i_k)
    {
        // nothing to do
        if (i_k == 0)
        {
            return;
        }

        Node * curr = m_head;
        std::size_t cnt = 1;
        // current node will either point to k-th node or end of list.
        while (cnt < i_k && curr != nullptr)
        {
            curr = curr->next;
            cnt++;
        }

        // rotation step is greater or equal to the list size.
        if (curr == nullptr)
        {
            return;
        }

        // store k-th node
        Node * kth_node = curr;

        // move to the last node in list
        while (curr->next != nullptr)
        {
            curr = curr->next;
        }

        // change next of last node to previous head
        curr->next = m_head;
        // head now points to the (k+1)-th node
        m_head = kth_node->next;
        // k-th node will be last node
        kth_node->next = nullptr;
    }

    /**
     * @brief Gets number of node in the list.
     * @return Size of list.
     */
    std::size_t size() const
    {
        std::size_t len = 0;
        // store pointer to head node
        Node * head = m_head;
        // go through list
        while (head != nullptr)
        {
            // increment size
            len++;
            // go to the next node
            head = head->next;
        }

        return len;
    }

    /**
     * @brief Prints content of the list.
     */
    friend std::ostream& operator<<(std::ostream & os, const SinglyLinkedList<ValueType> & i_list)
    {
        const Node * head = i_list.head();
        while (head != nullptr)
        {
            os << head->data << " ";
            head = head->next;
        }
        return os;
    }

    /**
     * Destructor.
     */
    ~SinglyLinkedList()
    {
        Node * head;
        while (m_head != nullptr)
        {
            // copy head
            head = m_head;
            // reset pointer
            m_head = m_head->next;
            // free memory
            delete head;
        }
    }

private:
    /**
     * @brief Definition of one node in linked list.
     */
    struct Node
    {
        ValueType data;      /**< Data stored in node.      */
        Node * next;          /**< Pointer to the next node. */
    };

    Node * m_head;           /**< Head of list.              */

    /**
     * @brief Recursively reverse the list.
     * @param[in,out] o_head Double pointer to the head of list.
     */
    void p_reverse_recursive(Node ** io_head)
    {
        Node *head = nullptr, *rest = nullptr;

        // check if list is empty
        if (*io_head == nullptr)
        {
            return;
        }

        // divide list on two parts
        head = *io_head;
        rest = head->next;

        // list has only one node
        if (rest == nullptr)
        {
            return;
        }

        // reverse tail of the list
        p_reverse_recursive(&rest);
        // link reversed tail to head
        head->next->next = head;

        head->next = nullptr;

        // reset head of the list
        *io_head = rest;
    }

    /**
     * @brief Reverse list in groups of given size.
     * @param[in] i_head Pointer to the head of the list.
     * @param[in] i_k Group size.
     * @return New head of the list.
     */
    Node * p_reverse_block(Node * i_head, const std::size_t i_k)
    {
        Node *curr = i_head, *prev = nullptr, *next = nullptr;
        std::size_t cnt = 0;

        // reverse first block of k nodes
        while (curr != nullptr && cnt < i_k)
        {
            next = curr->next;
            // reverse link
            curr->next = prev;
            // go to next node
            prev = curr;
            curr = next;
            // increment number of nodes in group
            cnt++;
        }

        // recursively reverse rest of the list
        if (next != nullptr)
        {
            i_head->next = p_reverse_block(next, i_k);
        }

        return prev;
    }
};
