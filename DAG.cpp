#include <vector>
#include <limits>

#include "DAG.hpp"

/**
* @brief Helper function for topological sort.
* @param[in] i_start Source vertex.
* @param[in,out] io_visited List of visited nodes.
* @param[out] o_stack Vertices in topologicaly sorted order.
*/
void DAG::topological_sort_util(int i_start, std::vector<bool> & io_visited, std::stack<int> & o_stack) const
{
    // mark vertex as visited
    io_visited[i_start] = true;

    // visit neighbors
    for (std::size_t pos = 0; pos < m_list[i_start].size(); ++pos)
    {
        int neighbor = m_list[i_start][pos].vertex;
        if (!io_visited[neighbor])
        {
            topological_sort_util(neighbor, io_visited, o_stack);
        }
    }

    // add current vertex
    o_stack.push(i_start);
}

/**
* @brief Sort graph in topological order.
* @return Vertices in topologicaly sorted oreder.
*/
std::stack<int> DAG::topological_sort() const
{
    // number of vertices in graph
    const std::size_t n = size();

    // result of topological sort
    std::stack<int> st;

    // list of visited vertices
    std::vector<bool> visited(n, false);

    // visit all vertices
    for (std::size_t vertex = 0; vertex < n; ++vertex)
    {
        if (!visited[vertex])
        {
            // start topological sort
            topological_sort_util(vertex, visited, st);
        }
    }

    return st;
}

/**
* @brief Calculates shortest paths from source vertex to all other vertices.
* @param[in] i_start Source vertex.
* @return List of (Vertex, Distance) pairs.
*/
std::vector<std::pair<int, int>> DAG::shortes_path(int i_start) const
{
    // number of vertices in graph
    const std::size_t n = size();

    // set all distances to INF
    std::vector<int> dists(n, std::numeric_limits<int>::max());

    // get vertices in topologicaly soreted order
    std::stack<int> ts = topological_sort();

    // distance to source vertex
    dists[i_start] = 0;

    // visit all vertices
    while (!ts.empty())
    {
        // get top most vertex
        int vertex = ts.top();
        ts.pop();

        if (dists[vertex] < std::numeric_limits<int>::max())
        {
            // visit neigbors
            for (std::size_t pos = 0; pos < m_list[vertex].size(); ++pos)
            {
                int neighbor = m_list[vertex][pos].vertex;
                int weight = m_list[vertex][pos].weight;

                // update distance
                if (dists[neighbor] > dists[vertex] + weight)
                {
                    dists[neighbor] = dists[vertex] + weight;
                }
            }
        }
    }

    std::vector<std::pair<int, int>> res;
    for (std::size_t pos = 0; pos < n; ++pos)
    {
        res.push_back(std::make_pair(pos, dists[pos]));
    }

    return res;
}
