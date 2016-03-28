#include "UnionFind.hpp"

/**
* @brief Finds parent of given vertex.
* @param[in] i_vertex Input vertex.
* @return Parent of vertex.
*/
int UnionFind::find(int i_vertex) const
{
    if (m_parents[i_vertex] == -1)
    {
        return i_vertex;
    }
    return find(m_parents[i_vertex]);
}

/**
* @brief Function that do union of two subsets.
* @param[in] i_first First vertex.
* @param[in] i_second Second vertex.
*/
void UnionFind::make_union(int i_first, int i_second)
{
    // find parents
    int p1 = find(i_first);
    int p2 = find(i_second);

    m_parents[p1] = p2;
}
