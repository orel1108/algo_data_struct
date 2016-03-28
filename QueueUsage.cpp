#include <vector>

#include "Dequeue.hpp"
#include "QueueUsage.hpp"

/**
* @brief Find starting position to perform circular tour.
* @param[in] i_petrol_pumps Pair of values: first = amount of petrol that petrol pump has and second = distance to next petrol pump.
* @return First starting position to complete the circle and -1 if tour not found.
*/
int findStart(const std::vector<std::pair<int, int>> & i_petrol_pumps)
{
    int start = 0, end = 1;

    // number of petrols
    const std::size_t n = i_petrol_pumps.size();

    // find amount of petrol left after traveling to next petrol pump
    int curr_petrol = i_petrol_pumps[0].first - i_petrol_pumps[0].second;

    // lookup starting position
    while (start < end || curr_petrol < 0)
    {
        // start removing petrol pumps from the begining until cuurent petrol become >= 0
        while (curr_petrol < 0 && start != end)
        {
            curr_petrol -= i_petrol_pumps[start].first - i_petrol_pumps[start].second;
            start = (start + 1) % n;

            // case when we consider 0 as start again
            if (start == 0)
            {
                return -1;
            }
        }

        // add new petrol pump
        curr_petrol += i_petrol_pumps[end].first - i_petrol_pumps[end].second;
        // move to next petrol pump
        end = (end + 1) % n;
    }

    return start;
}

/**
* @brief Finds maximum in each contiguous subarray of given array.
* @param[in] i_buf Array of values.
* @param[in] i_k Size of subarrays.
* @return Array of maximum values.
*/
std::vector<int> maxOfAllSubarrays(const std::vector<int> & i_buf, std::size_t i_k)
{
    // auxiliary data structrure
    Dequeue<std::size_t> dq;

    // resulting array
    std::vector<int> res;

    // traverse first k items
    for (std::size_t pos = 0; pos < i_k; pos++)
    {
        // remove positions with smaller elements
        while (!dq.empty() && i_buf[pos] >= i_buf[dq.last()])
        {
            dq.delete_last();
        }
        // add current position
        dq.insert_last(pos);
    }

    // process rest elements
    for (std::size_t pos = i_k; pos < i_buf.size(); pos++)
    {
        // add largest element from previous window
        res.push_back(i_buf[dq.front()]);

        // remove positions that are out of window of size k
        while (!dq.empty() && dq.front() <= pos - i_k)
        {
            dq.delete_front();
        }

        // remove positions with smaller elements
        while (!dq.empty() && i_buf[pos] >= i_buf[dq.last()])
        {
            dq.delete_last();
        }
        // add current position
        dq.insert_last(pos);
    }

    // add maximum element of last window
    res.push_back(i_buf[dq.front()]);

    return res;
}

/**
* @brief Generates binary representation for all value from 1 to n.
* @param[in] i_n Upper limit.
* @return Binary representations of all numbers from 1 to n.
*/
std::vector<std::string> genBinaryReps(int i_n)
{
    // resulting array
    std::vector<std::string> res;

    // auxiliary data structrure
    Dequeue<std::string> dq;

    // add first binary number
    dq.insert_last("1");

    // algorithm similar to DFS for binary trees
    while (i_n--)
    {
        // remove topmost item
        std::string s = dq.front();
        dq.delete_front();

        res.push_back(s);

        // copy before changing original string
        std::string c = s;

        // add two neighbors
        dq.insert_last(s.append("0"));
        dq.insert_last(c.append("1"));
    }

    return res;
}
