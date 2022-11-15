#pragma once

namespace Fetch
{

#ifndef NETWORK_H
#define NETWORK_H
#endif

    /**
     * @brief Setup the fetch class
     * @return void
     */
    void setup();

    /**
     * @brief Fetches the total number of open issues from the GitHub API
     * @param delayTime Time to wait each iteration
     * @return std::optional<int> Total issue count
     */
    std::optional<int> loop(int delayTime);

    /**
     * @brief Fetches the total number of open issues from the GitHub API
     * @return std::optional<int> Total issue count
     */
    std::optional<int> fetchTotalOpenIssues();
}
