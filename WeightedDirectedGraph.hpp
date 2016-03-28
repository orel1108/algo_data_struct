#pragma once

#include <vector>

class WeightedDirectedGraph
{
public:
    typedef std::vector<int>                 Row;
    typedef std::vector<std::vector<int>>    Matrix;

    /**
    * @brief Constructor.
    * @param[in] i_size Number of vertices in graph.
    */
    WeightedDirectedGraph(const std::size_t i_size)
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
    * @param[in] i_src Source vertex.
    * @param[in] i_dst Destination vertex.
    * @param[in] i_w Edge weight.
    */
    void add_edge(const int i_src, const int i_dst, const int i_w);

    /**
    * @brief Finds shortest path from source vertex to each vertex in graph using Bellman-Ford algorithm.
    * @param[in] i_start Source vertex.
    * @return Pait Indicator and Array of pairs (Vertex, Distance), where indicator idecates negative loop.
    */
    std::pair<bool, std::vector<std::pair<int, int>>> bellman_ford(int i_start) const;

    /**
     * @brief Finds shortest paths between all pairs of vertices.
     * @return Matrix with resulting distances.
     */
    Matrix floyd_warshell() const;

    /**
     * @brief Finds shortest path between to vertices which contains exactly k edges.
     * @param[in] i_src Source vertex.
     * @param[in] i_dst Destination vertex.
     * @param[in] i_k Number of edges.
     * @return Distance from source vertex to destination vertex.
     */
    int shortest_path(int i_src, int i_dst, int i_k) const;

private:
    Matrix m_matrix;                         /**< Adjacency matrix.            */
    std::size_t m_size;                      /**< Number of vertices in graph. */
};