#pragma once

#include <vector>
#include <set>
#include <queue>
#include <stack>

/**
 * @brief Implementation of Graph (based on adjacency list).
 */
class Graph
{
public:
    /**
     * @brief Constructor.
     * @param[in] i_num_nodes Number of nodes in graph.
     */
    Graph(std::size_t i_num_nodes)
        : m_num_nodes(i_num_nodes)
    {
        m_list = std::vector<std::set<int>>(m_num_nodes, std::set<int>());
    }

    /**
     * @brief Gets number of nodes in graph.
     */
    const std::size_t size() const
    {
        return m_num_nodes;
    }

    /**
     * @brief Add new edge to graph.
     * @param[in] i_src Source node.
     * @param[in] i_dst Destination node.
     */
    void add_edge(int i_src, int i_dst);

    /**
     * @brief Breadth First Traversal of graph.
     * @tparam Func Type of function.
     * @param[in] func Function which will be applied to each node during traversal.
     * @param[in] i_start Starting point.
     */
    template<class Func>
    void bfs(Func func, int i_start);

    /**
    * @brief Depth First Traversal of graph.
    * @tparam Func Type of function.
    * @param[in] func Function which will be applied to each node during traversal.
    * @param[in] i_start Starting point.
    */
    template<class Func>
    void dfs(Func func, int i_start);

    /**
     * @brief Detects cycle in graph.
     * @return True if graph has cycle and False otherwise.
     */
    bool has_cycle() const;

    /**
     * @brief Topological sort of graph.
     * @return Nodes from topological sort.
     */
    std::stack<int> topological_sort() const;

    /**
     * @brief Checks wether graph can be divided into two sets, 
     * such that every edge connects one vertex from one set and other vertex from other.
     * @param[in] i_start Starting point.
     * @return True if graph can be partitioned and False otherwise.
     */
    bool is_bipartite(int i_start) const;

private:
    std::vector<std::set<int>> m_list;  /**< Graph representation.      */
    std::size_t m_num_nodes;            /**< Number of nodes in graph.  */

    /**
     * @brief Depth First Traversal of graph.
     * @tparam Func Type of function.
     * @param[in] func Function which will be applied to each node during traversal.
     * @param[in] i_start Starting point.
     * @param[in,out] io_visited Array of visited nodes.
     */
    template<class Func>
    void dfs_util(Func func, int i_start, std::vector<bool> & io_visited);

    /**
     * @brief Helper function, detect if graph is cyclic.
     * @param[in] i_start Starting point.
     * @param[in,out] io_visited Visited nodes.
     * @param[in,out] io_stack Recursion stack.
     * @return True if graph has cycle and False otherwise.
     */
    bool has_cycle_util(int i_start, std::vector<bool> & io_visited, std::vector<bool> & io_stack) const;

    /**
     * @brief Helper function for topological sort.
     * @param[in] i_start Starting node.
     * @param[in] io_visited Array with visited nodes.
     * @param[in] o_stack Resuting topological sort.
     */
    void topological_sort_util(int i_start, std::vector<bool> & io_visited, std::stack<int> & o_stack) const;
};

/**
* @brief Breadth First Traversal of graph.
* @tparam Func Type of function.
* @param[in] func Function which will be applied during traversal.
* @param[in] i_start Starting point.
*/
template<class Func>
inline void Graph::bfs(Func func, int i_start)
{
    // get number of nodes
    const std::size_t n = size();

    // mark all nodes as non-visited
    std::vector<bool> visited(n, false);

    // auxiliary data structure
    std::queue<int> q;

    // enqueue starting node
    q.push(i_start);
    // mark as visited
    visited[i_start] = true;

    // process all nodes
    while (!q.empty())
    {
        // pop first node
        int node = q.front();
        q.pop();

        // process node
        func(node);

        // go through neighbors
        std::set<int>::iterator it = m_list[node].begin();
        for (; it != m_list[node].end(); ++it)
        {
            if (!visited[*it])
            {
                // add node
                q.push(*it);
                // mark as visited
                visited[*it] = true;
            }
        }
    }
}

/**
* @brief Depth First Traversal of graph.
* @tparam Func Type of function.
* @param[in] func Function which will be applied to each node during traversal.
* @param[in] i_start Starting point.
*/
template<class Func>
inline void Graph::dfs(Func func, int i_start)
{
    // number of nodes in graph
    const std::size_t n = size();

    // visited nodes
    std::vector<bool> visited(n, false);

    dfs_util(func, i_start, visited);
}

/**
* @brief Depth First Traversal of graph.
* @tparam Func Type of function.
* @param[in] func Function which will be applied to each node during traversal.
* @param[in] i_start Starting point.
* @param[in] io_visited Array of visited nodes.
*/
template<class Func>
inline void Graph::dfs_util(Func func, int i_start, std::vector<bool>& io_visited)
{
    // mark node as visited
    io_visited[i_start] = true;

    // process node
    func(i_start);

    // go through neighbors
    std::set<int>::iterator it = m_list[i_start].begin();
    for (; it != m_list[i_start].end(); ++it)
    {
        if (!io_visited[*it])
        {
            dfs_util(func, *it, io_visited);
        }
    }
}
