// WORKED EXAMPLE. Cover the normal case, the edges, and the "not found" case.

#include <string>
#include <vector>

#include "framework.hpp"
#include "h235/algorithms/binary_search.hpp"

TEST_CASE("binarySearch: finds items anywhere in the vector") {
    std::vector<int> v{1, 3, 5, 7, 9, 11};
    CHECK_EQ(h235::binarySearch(v, 1), 0);
    CHECK_EQ(h235::binarySearch(v, 7), 3);
    CHECK_EQ(h235::binarySearch(v, 11), 5);
}

TEST_CASE("binarySearch: returns -1 when missing") {
    std::vector<int> v{1, 3, 5};
    CHECK_EQ(h235::binarySearch(v, 0), -1);
    CHECK_EQ(h235::binarySearch(v, 4), -1);
    CHECK_EQ(h235::binarySearch(v, 6), -1);
}

TEST_CASE("binarySearch: empty and single-element vectors") {
    CHECK_EQ(h235::binarySearch(std::vector<int>{}, 1), -1);
    CHECK_EQ(h235::binarySearch(std::vector<int>{4}, 4), 0);
}

TEST_CASE("binarySearch: works with strings") {
    std::vector<std::string> v{"apple", "kiwi", "mango", "pear"};
    CHECK_EQ(h235::binarySearch(v, std::string("mango")), 2);
}
