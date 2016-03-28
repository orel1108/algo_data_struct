#pragma once

#include <vector>
#include <string>

/**
 * @brief Class implements reverse DNS look up.
 */
class ReverseDNSCache
{
public:
    /**
     * @brief Definition of node.
     */
    struct Node
    {
        std::string url;                /**< URL stored in node.         */
        std::vector<Node *> child;      /**< Children nodes.             */
        bool is_leaf;                   /**< Indicator of a leaf node.   */

        /**
         * @brief Default constructor.
         */
        Node()
            : url(std::string())
            , child(std::vector<Node *>(11, nullptr))
            , is_leaf(false)
        {}
    };

    /**
     * @brief Default constructor.
     */
    ReverseDNSCache()
        : m_root(new Node)
    {}

    /**
     * @brief Add IP address and corresponding URL.
     * @param[in] i_ip IP address.
     * @param[in] i_url URL.
     */
    void insert(const std::string & i_ip, const std::string & i_url);

    /**
     * @brief Reverse DNS search.
     * @param[in] i_ip IP address.
     * @return URL which corresponds to given IP.
     */
    std::string search(const std::string & i_ip) const;

private:
    Node * m_root; /**< root of trie. */
};
