#include <vector>
#include <limits>
#include <algorithm>

#include "UnionFind.hpp"
#include "WeightedGraph.hpp"

namespace
{
    /**
     * @brief Find minimal key.
     * @param[in] i_keys Key values.
     * @oaram[in] i_mst_set Vertices already in mst.
     * @param[in] i_size Number of vertices in graph.
     * @return Index of minimal key.
     */
    int min_key(const std::vector<int> & i_keys, const std::vector<bool> & i_mst_set, const std::size_t i_size)
    {
        int min_value = std::numeric_limits<int>::max(), min_idx = 0;

        for (int idx = 0; idx < (int)i_size; ++idx)
        {
            if (!i_mst_set[idx] && i_keys[idx] < min_value)
            {
                min_value = i_keys[idx];
                min_idx = idx;
            }
        }

        return min_idx;
    }
}

/**
* @brief Add edge to graph.
* @param[in] i_v1 First vertex.
* @param[in] i_v2 Second vertex.
* @param[in] i_w Edge weight.
*/
void WeightedGraph::add_edge(const int i_v1, const int i_v2, const int i_w)
{
    m_matrix[i_v1][i_v2] = i_w;
    m_matrix[i_v2][i_v1] = i_w;
}

/**
* @brief Contructs Minimum Spanning Tree using Prim's algorithm.
* @return List of edges from MST.
*/
std::vector<std::pair<int, int>> WeightedGraph::prim_mst() const
{
    const std::size_t n = size();

    // array will contain parent of each node
    std::vector<int> parents(n, -1);
    // key values
    std::vector<int> keys(n, std::numeric_limits<int>::max());
    // vertices already in MST
    std::vector<bool> mst_set(n, false);

    // include first vertex in mst
    keys[0] = 0;
    mst_set[0] = true;

    // add n - 1 vertices
    for (std::size_t vcnt = 0; vcnt < n - 1; ++vcnt)
    {
        // find vertex with minimum key
        int vertex = min_key(keys, mst_set, n);
        // add vertex to mst
        mst_set[vertex] = true;

        for (std::size_t ucnt = 0; ucnt < n; ++ucnt)
        {
            if (m_matrix[vertex][ucnt] &&            // exists edge
                mst_set[ucnt] == false &&            // vertex not in mst
                m_matrix[vertex][ucnt] < keys[ucnt]) // update key if greater then key in matrix
            {
                parents[ucnt] = vertex;
                keys[ucnt] = m_matrix[vertex][ucnt];
            }
        }
    }

    // construct mst
    std::vector<std::pair<int, int>> mst;
    for (std::size_t cnt = 1; cnt < n; ++cnt)
    {
        mst.push_back(std::make_pair(parents[cnt], cnt));
    }

    return mst;
}

/**
* @brief Contructs Minimum Spanning Tree using Kruskal's algorithm.
* @return List of edges from MST.
*/
std::vector<std::pair<int, int>> WeightedGraph::kruskal_mst() const
{
    // definition of graph's edge
    struct Edge
    {
        int weight;
        int u, v;
    };

    // compare two edges
    struct Compare
    {
        bool operator()(Edge i_left, Edge i_right) { return i_left.weight < i_right.weight; }
    } comp;

    // list of edges
    std::vector<Edge> edges;

    const std::size_t n = size();

    // traverse adjacency matrix
    for (std::size_t row = 0; row < n; ++row)
    {
        for (std::size_t col = 0; col < n; ++col)
        {
            if (m_matrix[row][col] != 0)
            {
                Edge e;
                e.u = row;
                e.v = col;
                e.weight = m_matrix[row][col];
                // add edge
                edges.push_back(e);
            }
        }
    }

    // sort edge by weight
    std::sort(edges.begin(), edges.end(), comp);

    // auxiliary data structure
    UnionFind uf(n);

    // resulting tree
    std::vector<std::pair<int, int>> mst;

    // check all edges
    for (std::size_t pos = 0; pos < edges.size(); ++pos)
    {
        Edge e = edges[pos];

        // find parents
        int u = uf.find(e.u);
        int v = uf.find(e.v);

        // check that adding edge doesn't cause cycle
        if (u != v)
        {
            // add edge to mst
            mst.push_back(std::make_pair(e.u, e.v));
            // add edge
            uf.make_union(u, v);
        }
    }

    return mst;
}

/**
* @brief Finds shortest path from source vertex to each vertex in graph.
* @param[in] i_start Source vertex.
* @return Array of pairs (Vertex, Distance).
*/
std::vector<std::pair<int, int>> WeightedGraph::dijkstra(int i_start) const
{
    // number of vertices in graph
    const std::size_t n = size();

    // distances to vertices
    std::vector<int> dists(n, std::numeric_limits<int>::max());
    // indicates wether vertex in shortest path tree
    std::vector<bool> shortest_path_tree(n, false);

    // set distance to source vertex
    dists[i_start] = 0;

    // add other vertices
    for (std::size_t cnt = 0; cnt < n - 1; ++cnt)
    {
        // find minimum key
        int mkey = min_key(dists, shortest_path_tree, n);
        // add vertex to shortest path tree
        shortest_path_tree[mkey] = true;

        // update distances
        for (std::size_t vertex = 0; vertex < n; ++vertex)
        {
            if (m_matrix[mkey][vertex]                            &&    // check if edge exists
                !shortest_path_tree[vertex]                       &&    // vertex not in tree
                dists[mkey] != std::numeric_limits<int>::max()    &&
                dists[mkey] + m_matrix[mkey][vertex] < dists[vertex])
            {
                // update distance
                dists[vertex] = dists[mkey] + m_matrix[mkey][vertex];
            }
        }
    }

    std::vector<std::pair<int, int>> res;
    for (std::size_t vertex = 0; vertex < dists.size(); ++vertex)
    {
        res.push_back(std::make_pair(vertex, dists[vertex]));
    }

    return res;
}
