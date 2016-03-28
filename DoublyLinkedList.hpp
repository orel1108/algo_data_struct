#pragma once

#include <iostream>

namespace
{
    /**
    * @brief Swaps two values.
    * @param[in,out] io_left Pointer to left value.
    * @param[in,out] io_right Pointer to right value.
    */
    template<class ItemType>
    void swap(ItemType * io_left, ItemType * io_right)
    {
        ItemType temp = *io_left;
        *io_left = *io_right;
        *io_right = temp;
    }
}

/**
* @brief Implementation of Doubly Linked List.
* @tparam ValueType Type of item stored in list.
*/
template<class ValueType>
class DoublyLinkedList
{
public:
    struct Node;                        /**< Forward declaration. */

    /**
     * @brief Default constructor.
     */
    DoublyLinkedList()
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
     * @brief Returns pointer to the last node in list.
     */
    Node * last() const
    {
        Node * curr = m_head;
        while (curr != nullptr && curr->next != nullptr)
        {
            curr = curr->next;
        }
        return curr;
    }

    /**
     * @brief Insert new node at the front of the list.
     * @param[in] i_data Data stored in new node.
     */
    void push_front(const ValueType & i_data)
    {
        Node * new_node = new Node;
        // store data
        new_node->data = i_data;
        // next of new node will be head
        new_node->next = m_head;
        // previous of new node will be NULL
        new_node->prev = nullptr;

        // change prevoius node of head
        if (m_head != nullptr)
        {
            m_head->prev = new_node;
        }
        // reset head
        m_head = new_node;
    }

    /**
    * @brief Insert new node at the end of the list.
    * @param[in] i_data Data stored in new node.
    */
    void push_back(const ValueType & i_data)
    {
        Node * new_node = new Node;
        // store data
        new_node->data = i_data;
        // set next node to NULL
        new_node->next = nullptr;

        Node * last = m_head;
        // case of empty list
        if (last == nullptr)
        {
            new_node->prev = nullptr;
            m_head = new_node;
        }
        else
        {
            // move to the last node
            while (last->next != nullptr)
            {
                last = last->next;
            }
            // create link to the last node
            last->next = new_node;
            // make last node as a previous of new node
            new_node->prev = last;
        }
    }

    /**
    * @brief Insert new node after given node.
    * @param[in,out] io_prev Pointer to the previous node.
    * @param[in] i_data Data stored in new node.
    */
    void insert_after(Node * io_prev, const ValueType & i_data)
    {
        if (io_prev == nullptr)
        {
            std::cerr << "Previous node cannot be NULL" << std::endl;
            return;
        }

        Node * new_node = new Node;
        // store data
        new_node->data = i_data;

        // create link to the next node
        new_node->next = io_prev->next;
        // next of previous node points to new node
        io_prev->next = new_node;
        // create link to previous node
        new_node->prev = io_prev;
        // change previous of next node
        if (new_node->next != nullptr)
        {
            new_node->next->prev = new_node;
        }
    }

    /**
    * @brief Insert new node before given node.
    * @param[in,out] io_next Pointer to the next node.
    * @param[in] i_data Data stored in new node.
    */
    void insert_before(Node * io_next, const ValueType & i_data)
    {
        if (io_next == nullptr)
        {
            std::cerr << "Next node cannot be NULL" << std::endl;
            return;
        }

        Node * new_node = new Node;
        // store data
        new_node->data = i_data;

        // create link to the previous node
        new_node->prev = io_next->prev;
        // change previous node
        io_next->prev = new_node;
        // create link to next node
        new_node->next = io_next;
        // change next of prevoius node
        if (new_node->prev != nullptr)
        {
            new_node->prev->next = new_node;
        }
        // insert before head
        else
        {
            m_head = new_node;
        }
    }

    /**
     * @brief Removes head node from the list.
     */
    void pop_front()
    {
        // check if list is not empty
        if (m_head != nullptr)
        {
            Node * curr = m_head;
            if (curr->next != nullptr)
            {
                // change head
                m_head = curr->next;
                // change previous node of head
                m_head->prev = nullptr;
            }
            else
            {
                m_head = nullptr;
            }
            // free memory
            delete curr;
        }
    }


    /**
     * @brief Removes last node from the list.
     */
    void pop_back()
    {
        // check if list is not empty
        if (m_head != nullptr)
        {
            Node * curr = m_head;
            // move to the last node
            while (curr->next != nullptr)
            {
                curr = curr->next;
            }

            // list contains at least two nodes
            if (curr->prev != nullptr)
            {
                curr->prev->next = nullptr;
            }
            // else remove head
            else
            {
                m_head = nullptr;
            }
            delete curr;
        }
    }

    /**
     * @brief Removes node from list with given key.
     * @param[in] i_key Value of key.
     */
    void delete_node(const ValueType & i_key)
    {
        // check if list isn't empty
        if (m_head != nullptr)
        {
            Node * curr = m_head;
            // look up node with given key
            while (curr != nullptr && curr->data != i_key)
            {
                curr = curr->next;
            }
            // key not found
            if (curr == nullptr)
            {
                return;
            }

            // key found in last node
            if (curr->next == nullptr)
            {
                // list has only one node
                if (curr->prev == nullptr)
                {
                    m_head = nullptr;
                }
                else
                {
                    // unlink last node
                    curr->prev->next = nullptr;
                }
            }
            else
            {
                // change previous in the next node
                curr->next->prev = curr->prev;
                // if current node is intermediate node
                if (curr->prev != nullptr)
                {
                    curr->prev->next = curr->next;
                }
                // else key found at the head
                else
                {
                    m_head = curr->next;
                }
            }
            // free memory
            delete curr;
        }
    }

    /**
     * @brief Reverses list.
     */
    void reverse()
    {
        Node *tmp = nullptr, *curr = m_head;
        // swap next and prev pointers
        while (curr != nullptr)
        {
            // swap pointers
            tmp = curr->prev;
            curr->prev = curr->next;
            curr->next = tmp;

            // move to next node
            curr = curr->prev;
        }

        // check if list contains at least two nodes
        if (tmp != nullptr)
        {
            m_head = tmp->prev;
        }
    }

    /**
     * @brief Sort list using quicksort algorithm.
     */
    void quicksort()
    {
        // get last element
        Node * last_node = last();
        p_quicksort(m_head, last_node);
    }

    /**
    * @brief Sort list using mergesort algorithm.
    */
    void mergesort()
    {
        m_head = p_mergesort(m_head);
    }

    /**
    * @brief Prints content of the list.
    */
    friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<ValueType> & i_list)
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
    ~DoublyLinkedList()
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
        ValueType data;      /**< Data stored in node.          */
        Node * next;          /**< Pointer to the next node.     */
        Node * prev;          /**< Pointer to the previous node. */
    };

    Node * m_head;           /**< Head of list.                 */

    /**
     * @brief Performs partittion on list.
     * @param[in] i_left Pointer to left node of list.
     * @param[in] i_right Pointer to right node of list.
     */
    Node * p_partition(Node * i_left, Node * i_right)
    {
        // pivot will be last element
        const ValueType pivot = i_right->data;

        // similar to i = -1 in quicksort of array
        Node * ipos = i_left->prev;
        for (Node * jpos = i_left; jpos != i_right; jpos = jpos->next)
        {
            if (jpos->data <= pivot)
            {
                // i++
                ipos = (ipos == nullptr) ? i_left : ipos->next;
                // place smaller elements to left of pivot
                swap(&(ipos->data), &(jpos->data));
            }
        }

        // i++
        ipos = (ipos == nullptr) ? i_left : ipos->next;
        // set pivot onto correct position
        swap(&(ipos->data), &(i_right->data));

        return ipos;
    }

    /**
     * @brief Sorts part of list.
     * @param[in] i_left Pointer to left node of list.
     * @param[in] i_right Pointer to right node of list.
     */
    void p_quicksort(Node * i_left, Node * i_right)
    {
        if (i_left != nullptr && i_right != nullptr && i_left != i_right->next)
        {
            // place smaller elements to left and greater to right of pivot
            Node * p = p_partition(i_left, i_right);
            // sort left side
            p_quicksort(i_left, p->prev);
            // sort right side
            p_quicksort(p->next, i_right);
        }
    }

    /**
     * @brief Merges two sorted lists.
     * @param[in] i_left Pointer to the head of left list.
     * @param[in] i_right Pointer to the head of right list.
     */
    Node * p_merge(Node * i_left, Node * i_right)
    {
        // left list is empty
        if (i_left == nullptr)
        {
            return i_right;
        }

        // right list is empty
        if (i_right == nullptr)
        {
            return i_left;
        }

        if (i_left->data < i_right->data)
        {
            // place at the top of list
            i_left->next = p_merge(i_left->next, i_right);
            // change previous of next pointer
            i_left->next->prev = i_left;
            i_left->prev = nullptr;
            return i_left;
        }
        else
        {
            // place at the top of list
            i_right->next = p_merge(i_left, i_right->next);
            // change previous of next pointer
            i_right->next->prev = i_right;
            i_right->prev = nullptr;
            return i_right;
        }
    }

    /**
     * @brief Splits list into 2 halfs.
     */
    Node * p_split(Node * i_head)
    {
        Node *fast = i_head, *slow = i_head;
        while (fast->next != nullptr && fast->next->next != nullptr)
        {
            // move by two nodes
            fast = fast->next->next;
            // move by one node
            slow = slow->next;
        }

        // split
        Node * temp = slow->next;
        // unlink
        slow->next = nullptr;

        return temp;
    }

    /**
     * @brief Sorts list using mergesort algorithms.
     * @param[in] i_head Pointer to the head of list.
     */
    Node * p_mergesort(Node * i_head)
    {
        // list is empty or has only one node
        if (i_head == nullptr || i_head->next == nullptr)
        {
            return i_head;
        }
        // split list into two halfs
        Node * half = p_split(i_head);

        // recursively sort two halfs
        i_head = p_mergesort(i_head);
        half = p_mergesort(half);

        // merge sorted lists
        return p_merge(i_head, half);
    }
};
