#pragma once

#include <vector>

/**
 * @brief Weighted Undirected Graph.
 */
class WeightedGraph
{
public:
    typedef std::vector<int>                 Row;
    typedef std::vector<std::vector<int>>    Matrix;

    /**
     * @brief Constructor.
     * @param[in] i_size Number of vertices in graph.
     */
    WeightedGraph(const std::size_t i_size)
        : m_matrix(Matrix(i_size, Row(i_size)))
        , m_size(i_size)
    {}

    /**
     * @brief Gets number of vertices in graph.
     */
    std::size_t size() const
    {
        return m_size;
    }

    /**
     * @brief Add edge to graph.
     * @param[in] i_v1 First vertex.
     * @param[in] i_v2 Second vertex.
     * @param[in] i_w Edge weight.
     */
    void add_edge(const int i_v1, const int i_v2, const int i_w);

    /**
     * @brief Contructs Minimum Spanning Tree using Prim's algorithm.
     * @return List of edges from MST.
     */
    std::vector<std::pair<int, int>> prim_mst() const;

    /**
    * @brief Contructs Minimum Spanning Tree using Kruskal's algorithm.
    * @return List of edges from MST.
    */
    std::vector<std::pair<int, int>> kruskal_mst() const;

    /**
     * @brief Finds shortest path from source vertex to each vertex in graph using Dijkstra algorithm.
     * @param[in] i_start Source vertex.
     * @return Array of pairs (Vertex, Distance).
     */
    std::vector<std::pair<int, int>> dijkstra(int i_start) const;

private:
    Matrix m_matrix;                         /**< Adjacency matrix.            */
    std::size_t m_size;                      /**< Number of vertices in graph. */
};
