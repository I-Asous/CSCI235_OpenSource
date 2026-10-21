#pragma once

// WORKED EXAMPLE. Every algorithm contribution should look like this file:
//   - one header in include/h235/algorithms/<name>.hpp
//   - everything inside namespace h235
//   - a short comment that says what the function does and what it returns
//   - a matching test file in tests/algorithms/test_<name>.cpp

#include <vector>

namespace h235 {

namespace detail {

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

/// Recursive binary search over a vector sorted in ascending order.
/// Returns the index of target, or -1 if it is not present. Runs in O(log n).
template <class T>
int binarySearch(const std::vector<T>& items, const T& target) {
    return detail::binarySearch(items, target, 0, static_cast<int>(items.size()) - 1);
}

}  // namespace h235
