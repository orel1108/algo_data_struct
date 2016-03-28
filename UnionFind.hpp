#pragma once

#include <vector>

/**
 * @brief Union-Find algorithm implementation.
 */
class UnionFind
{
public:
    /**
     * @brief Constructor.
     * @param[in] i_num_vert Number of vertices in graph.
     */
    UnionFind(const std::size_t i_num_vert)
        : m_num_vert(i_num_vert)
        , m_parents(std::vector<int>(i_num_vert, -1))
    {}

    /**
     * @brief Returns size of graph.
     */
    std::size_t size() const
    {
        return m_num_vert;
    }

    /**
     * @brief Finds parent of given vertex.
     * @param[in] i_vertex Input vertex.
     * @return Parent of vertex.
     */
    int find(int i_vertex) const;

    /**
     * @brief Function that do union of two subsets.
     * @param[in] i_first First vertex.
     * @param[in] i_second Second vertex.
     */
    void make_union(int i_first, int i_second);

private:
    std::vector<int> m_parents; /**< Contains parent of each vertex. */
    std::size_t m_num_vert;     /**< Number of vertices in graph.    */
};
