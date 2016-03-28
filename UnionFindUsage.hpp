#pragma once

#include <vector>

/**
* @brief Checks wether graph has cycle.
* @param[in] i_edges List of graph edges.
* @param[in] i_size Number of vertices in graph.
* @return True if graph has cycle and False otherwise.
*/
bool has_cycle(const std::vector<std::pair<int, int>> & i_edges, const std::size_t i_size);
