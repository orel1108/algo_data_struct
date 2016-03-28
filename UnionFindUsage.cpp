#include "UnionFindUsage.hpp"
#include "UnionFind.hpp"

/**
* @brief Checks wether graph has cycle.
* @param[in] i_edges List of graph edges.
* @param[in] i_size Number of vertices in graph.
* @return True if graph has cycle and False otherwise.
*/
bool has_cycle(const std::vector<std::pair<int, int>> & i_edges, const std::size_t i_size)
{
    // auxiliary data structure
    UnionFind un(i_size);

    // iterate through all edges
    std::vector<std::pair<int, int>>::const_iterator it = i_edges.begin();
    for (; it != i_edges.end(); ++it)
    {
        int p1 = un.find(it->first);
        int p2 = un.find(it->second);
        // if parent in same subset than cycle detected
        if (p1 == p2)
        {
            return true;
        }

        // add edge
        un.make_union(p1, p2);
    }

    return false;
}
