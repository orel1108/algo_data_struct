#pragma once

#include <vector>
#include <string>

/**
 * @brief Find starting position to perform circular tour.
 * @param[in] i_petrol_pumps Pair of values: first = amount of petrol that petrol pump has and second = distance to next petrol pump.
 * @return First starting position to complete the circle.
 */
int findStart(const std::vector<std::pair<int, int>> & i_petrol_pumps);

/**
 * @brief Finds maximum in each contiguous subarray of given array.
 * @param[in] i_buf Array of values.
 * @param[in] i_k Size of subarrays.
 * @return Array of maximum values.
 */
std::vector<int> maxOfAllSubarrays(const std::vector<int> & i_buf, std::size_t i_k);

/**
 * @brief Generates binary representation for all value from 1 to n.
 * @param[in] i_n Upper limit.
 * @return Binary representations of all numbers from 1 to n.
 */
std::vector<std::string> genBinaryReps(int i_n);
