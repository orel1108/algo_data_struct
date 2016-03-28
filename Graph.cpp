#include "Graph.hpp"

#include <vector>
#include <set>

/**
* @brief Add new edge to graph.
* @param[in] i_src Source node.
* @param[in] i_dst Destination node.
*/
void Graph::add_edge(int i_src, int i_dst)
{
    m_list[i_src].insert(i_dst);
}

/**
* @brief Detects cycle in graph.
* @param[in] i_start Starting point.
* @return True if graph has cycle and False otherwise.
*/
bool Graph::has_cycle() const
{
    const std::size_t n = size();
    // visited nodes
    std::vector<bool> visited(n, false);
    // recursion stack
    std::vector<bool> stack(n, false);

    for (std::size_t v = 0U; v < n; ++v)
    {
        if (has_cycle_util(v, visited, stack))
        {
            return true;
        }
    }

    return false;
}

/**
* @brief Topological sort of graph.
* @return Nodes from topological sort.
*/
std::stack<int> Graph::topological_sort() const
{
    const std::size_t n = size();

    // result os sorting
    std::stack<int> s;
    std::vector<bool> visited(n, false);

    for (std::size_t pos = 0; pos < n; ++pos)
    {
        if (!visited[pos])
        {
            topological_sort_util(pos, visited, s);
        }
    }

    return s;
}

/**
* @brief Helper function, detect if graph is cyclic.
* @param[in] i_start Starting point.
* @param[in,out] io_visited Visited nodes.
* @param[in,out] io_stack Recursion stack.
* @return True if graph has cycle and False otherwise.
*/
bool Graph::has_cycle_util(int i_start, std::vector<bool>& io_visited, std::vector<bool>& io_stack) const
{
    if (!io_visited[i_start])
    {
        // mark as visited
        io_visited[i_start] = true;
        // push on stack
        io_stack[i_start] = true;

        // visit neighbors
        std::set<int>::iterator it = m_list[i_start].begin();
        for (; it != m_list[i_start].end(); ++it)
        {
            // recursive check if graph has cycle
            if (!io_visited[*it] && has_cycle_util(*it, io_visited, io_stack))
            {
                return true;
            }
            // if node on stack
            else if (io_stack[*it])
            {
                return true;
            }
        }
    }
    
    // remove vertex from recursion stack
    io_stack[i_start] = false;

    return false;
}

/**
* @brief Helper function for topological sort.
* @param[in] i_start Starting node.
* @param[in] io_visited Array with visited nodes.
* @param[in] o_stack Resuting topological sort.
*/
void Graph::topological_sort_util(int i_start, std::vector<bool> & io_visited, std::stack<int> & o_stack) const
{
    // mark as visited
    io_visited[i_start] = true;

    // explore neighbor nodes
    std::set<int>::const_iterator it = m_list[i_start].begin();
    for (; it != m_list[i_start].end(); ++it)
    {
        if (!io_visited[*it])
        {
            topological_sort_util(*it, io_visited, o_stack);
        }
    }

    // add node to result
    o_stack.push(i_start);
}

/**
* @brief Checks wether graph can be divided into two sets,
* such that every edge connects one vertex from one set and other vertex from other.
* @param[in] i_start Starting point.
* @return True if graph can be partitioned and False otherwise.
*/
bool Graph::is_bipartite(int i_start) const
{
    const std::size_t n = size();

    // set all colors to -1
    std::vector<int> colors(n, -1);
    // auxiliary data structure
    std::queue<int> q;

    q.push(i_start);
    // mark starting point
    colors[i_start] = 1;

    // process nodes
    while (!q.empty())
    {
        // remove top element
        int vertex = q.front();
        q.pop();

        // process neighbors
        std::set<int>::const_iterator it = m_list[vertex].begin();
        for (; it != m_list[vertex].end(); ++it)
        {
            // check if neighbor not visited yet
            if (colors[*it] == -1)
            {
                colors[*it] = 1 - colors[vertex];
                q.push(*it);
            }
            else if (colors[*it] == colors[vertex])
            {
                return false;
            }
        }
    }

    // all vertices processed
    return true;
}
