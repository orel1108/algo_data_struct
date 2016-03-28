#pragma once

#include <vector>
#include <stack>

class DAG
{
public:
    struct Edge
    {
        int vertex;
        int weight;

        Edge(int i_vertex, int i_weight)
            : vertex(i_vertex)
            , weight(i_weight)
        {}
    };

    /**
     * @brief Constructor.
     * @param[in] i_size Number of vertices in graph.
     */
    DAG(std::size_t i_size)
        : m_list(std::vector<std::vector<Edge>>(i_size))
        , m_size(i_size)
    {}

    /**
     * @brief Return number of vertices in graph.
     */
    std::size_t size() const
    {
        return m_size;
    }

    /**
     * @brief Add edge to graph.
     * @param[in] i_src Source vertex.
     * @param[in] i_dst Destination vertex.
     * @param[in] i_weight Weight of edge.
     */
    void add_edge(int i_src, int i_dst, int i_weight)
    {
        m_list[i_src].emplace_back(i_dst, i_weight);
    }

    /**
     * @brief Sort graph in topological order.
     * @return Vertices in topologicaly sorted oreder.
     */
    std::stack<int> topological_sort() const;

    /**
     * @brief Calculates shortest paths from source vertex to all other vertices.
     * @param[in] i_start Source vertex.
     * @return List of (Vertex, Distance) pairs.
     */
    std::vector<std::pair<int, int>> shortes_path(int i_start) const;

private:
    std::vector<std::vector<Edge>> m_list;     /**< Adjacency list.              */
    std::size_t m_size;                        /**< Number of vertices in graph. */

    /**
     * @brief Helper function for topological sort.
     * @param[in] i_start Source vertex.
     * @param[in,out] io_visited List of visited nodes.
     * @param[out] o_stack Vertices in topologicaly sorted order.
     */
    void topological_sort_util(int i_start, std::vector<bool> & io_visited, std::stack<int> & o_stack) const;
};
