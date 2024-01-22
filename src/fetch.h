#pragma once

namespace Fetch
{
    /**
     * @brief Fetches the total number of open issues from the GitHub API
     * @param delayTime Time to wait each iteration
     * @return std::optional<int> Total issue count
     */
    std::optional<int> fetchIssues(int delayTime);

    /**
     * @brief Fetches the total number of open issues from the GitHub API
     * @return std::optional<int> Total issue count
     */
    std::optional<int> fetchTotalOpenIssues();
}
