#include <vector>
#include <limits>
#include <algorithm>

#include "WeightedDirectedGraph.hpp"

/**
* @brief Add edge to graph.
* @param[in] i_src Source vertex.
* @param[in] i_dst Destination vertex.
* @param[in] i_w Edge weight.
*/
void WeightedDirectedGraph::add_edge(const int i_src, const int i_dst, const int i_w)
{
    m_matrix[i_src][i_dst] = i_w;
}


/**
* @brief Finds shortest path from source vertex to each vertex in graph using Bellman-Ford algorithm.
* @param[in] i_start Source vertex.
* @return Pait Indicator and Array of pairs (Vertex, Distance), where indicator idecates negative loop.
*/
std::pair<bool, std::vector<std::pair<int, int>>> WeightedDirectedGraph::bellman_ford(int i_start) const
{
    // number of vertices in graph
    const std::size_t n = size();

    // distances to vertices
    std::vector<int> dists(n, std::numeric_limits<int>::max());

    // set distance to source vertex
    dists[i_start] = 0;

    for (std::size_t cnt = 0; cnt < n - 1; ++cnt)
    {
        // relax each edge
        for (std::size_t row = 0; row < n; ++row)
        {
            for (std::size_t col = 0; col < n; ++col)
            {
                // if there are edge
                if (m_matrix[row][col])
                {
                    if (dists[row] != std::numeric_limits<int>::max() && dists[row] + m_matrix[row][col] < dists[col])
                    {
                        // relax
                        dists[col] = dists[row] + m_matrix[row][col];
                    }
                }
            }
        }
    }

    bool has_neg_cycle = false;

    // detect negative cycle
    for (std::size_t row = 0; row < n; ++row)
    {
        for (std::size_t col = 0; col < n; ++col)
        {
            // if there are edge
            if (m_matrix[row][col])
            {
                if (dists[row] != std::numeric_limits<int>::max() && dists[row] + m_matrix[row][col] < dists[col])
                {
                    has_neg_cycle = true;
                }
            }
        }
    }

    std::vector<std::pair<int, int>> res;
    for (std::size_t vertex = 0; vertex < dists.size(); ++vertex)
    {
        res.push_back(std::make_pair(vertex, dists[vertex]));
    }

    return std::make_pair(has_neg_cycle, res);
}

/**
* @brief Finds shortest paths between all pairs of vertices.
* @return Matrix with resulting distances.
*/
WeightedDirectedGraph::Matrix WeightedDirectedGraph::floyd_warshell() const
{
    // number of vertices in graph
    const std::size_t n = size();

    // resulting distances
    WeightedDirectedGraph::Matrix dists(n, WeightedDirectedGraph::Row(n, std::numeric_limits<int>::max()));
    for (std::size_t row = 0; row < n; ++row)
    {
        for (std::size_t col = 0; col < n; ++col)
        {
            if (row == col)
            {
                dists[row][col] = 0;
            }
            else if (m_matrix[row][col])
            {
                dists[row][col] = m_matrix[row][col];
            }
        }
    }

    // on each step w is intermediate point
    for (std::size_t w = 0; w < n; ++w)
    {
        // consider all pairs of vertices
        for (std::size_t u = 0; u < n; ++u)
        {
            for (std::size_t v = 0; v < n; ++v)
            {
                int d_uw = dists[u][w];
                int d_wv = dists[w][v];
                int d_uv = dists[u][v];
                if (d_uw < std::numeric_limits<int>::max() && 
                    d_wv < std::numeric_limits<int>::max() && 
                    d_uw + d_wv < d_uv)
                {
                    dists[u][v] = d_uw + d_wv;
                }
            }
        }
    }

    return dists;
}

/**
* @brief Finds shortest path between to vertices which contains exactly k edges.
* @param[in] i_src Source vertex.
* @param[in] i_dst Destination vertex.
* @param[in] i_k Number of edges.
* @return Distance from source vertex to destination vertex.
*/
int WeightedDirectedGraph::shortest_path(int i_src, int i_dst, int i_k) const
{
    // number of vertices in graph
    const std::size_t n = size();

    // 3D matrix for dynamic programming
    std::vector<std::vector<std::vector<int>>> matrix3D(n, std::vector<std::vector<int>>(n, std::vector<int>(i_k + 1)));

    // number of edges
    for (int num_edges = 0; num_edges < i_k + 1; ++num_edges)
    {
        for (std::size_t src = 0; src < n; ++src)           // from source vertex
        {
            for (std::size_t dst = 0; dst < n; ++dst)       // to destination vertex
            {
                matrix3D[src][dst][num_edges] = std::numeric_limits<int>::max();

                if (num_edges == 0 && src == dst)
                {
                    matrix3D[src][dst][num_edges] = 0;
                }

                // check if there edge between source and destination vertices
                if (num_edges == 1 && m_matrix[src][dst] > 0)
                {
                    matrix3D[src][dst][num_edges] = m_matrix[src][dst];
                }

                if (num_edges > 1)
                {
                    for (std::size_t inner = 0; inner < n; ++inner)
                    {
                        if (m_matrix[src][inner] < std::numeric_limits<int>::max() &&                // edge from source to inner vertex
                            src != inner && dst != inner                           &&                // inner vertex not same as either source or destination
                            matrix3D[inner][dst][num_edges - 1] < std::numeric_limits<int>::max())   // shortest path from inner node to destination using (k - 1) edge
                        {  
                            matrix3D[src][dst][num_edges] = std::min(matrix3D[src][dst][num_edges], m_matrix[src][inner] + matrix3D[inner][dst][num_edges - 1]);
                        }
                    }
                }
            }
        }
    }

    return matrix3D[i_src][i_dst][i_k];
}
