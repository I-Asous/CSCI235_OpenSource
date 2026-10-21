#pragma once

// WORKED EXAMPLE. Every algorithm contribution should look like this file:
//   - one header in include/h235/algorithms/<name>.hpp
//   - everything inside namespace h235
//   - a /** @brief ... */ comment above each function, with @param, @return,
//     @throws and @note as needed (see CONTRIBUTING.md)
//   - a matching test file in tests/algorithms/test_<name>.cpp

#include <vector>

namespace h235 {

namespace detail {

/**
 * @brief Helper function to recursively search
 * the range [first, last] of a sorted vector.
 * @param items The vector to search, sorted in ascending order.
 * @param target The value to look for.
 * @param first The index of the first element in the current range.
 * @param last The index of the last element in the current range.
 * @return The index of target, or -1 if it is not in the range.
 *
 * @note Each call halves the range, so the search runs in O(log n).
 *
 * Instead of calling this directly, use h235::binarySearch as a wrapper
 * that passes the full range of the vector.
 */
template <class T>
int binarySearch(const std::vector<T>& items, const T& target, int first, int last) {
    if (first > last) {
        return -1;
    }
    int mid = first + (last - first) / 2;
    if (items[mid] == target) {
        return mid;
    }
    if (target < items[mid]) {
        return binarySearch(items, target, first, mid - 1);
    }
    return binarySearch(items, target, mid + 1, last);
}

}  // namespace detail

/**
 * @brief Recursive binary search over a vector sorted in ascending order.
 * @param items The vector to search, sorted in ascending order.
 * @param target The value to look for.
 * @return The index of target, or -1 if it is not present.
 *
 * @note Runs in O(log n). If target appears more than once,
 * any one of its indices may be returned.
 */
template <class T>
int binarySearch(const std::vector<T>& items, const T& target) {
    return detail::binarySearch(items, target, 0, static_cast<int>(items.size()) - 1);
}

}  // namespace h235
