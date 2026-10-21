#include <algorithm>
#include <string>
#include <vector>

#include "framework.hpp"
#include "h235/ArrayBag.hpp"
#include "h235/LinkedBag.hpp"

namespace {

std::vector<int> sorted(std::vector<int> v) {
    std::sort(v.begin(), v.end());
    return v;
}

// Both bags share an interface, so run the same checks against each.
void checkBasicBehavior(h235::BagInterface<int>& bag) {
    CHECK(bag.isEmpty());
    CHECK(bag.add(3));
    CHECK(bag.add(1));
    CHECK(bag.add(3));
    CHECK_EQ(bag.getCurrentSize(), 3);
    CHECK_EQ(bag.getFrequencyOf(3), 2);
    CHECK(bag.contains(1));
    CHECK(!bag.contains(42));

    CHECK(bag.remove(3));
    CHECK_EQ(bag.getFrequencyOf(3), 1);
    CHECK(!bag.remove(42));
    CHECK_EQ(sorted(bag.toVector()), (std::vector<int>{1, 3}));

    bag.clear();
    CHECK(bag.isEmpty());
    CHECK_EQ(bag.getCurrentSize(), 0);
}

}  // namespace

TEST_CASE("ArrayBag: basic behavior") {
    h235::ArrayBag<int> bag;
    checkBasicBehavior(bag);
}

TEST_CASE("ArrayBag: add fails when full") {
    h235::ArrayBag<int> bag;
    for (int i = 0; i < h235::ArrayBag<int>::DEFAULT_CAPACITY; ++i) {
        CHECK(bag.add(i));
    }
    CHECK(!bag.add(-1));
}

TEST_CASE("LinkedBag: basic behavior") {
    h235::LinkedBag<int> bag;
    checkBasicBehavior(bag);
}

TEST_CASE("LinkedBag: copy is independent of original") {
    h235::LinkedBag<std::string> original;
    original.add("a");
    original.add("b");

    h235::LinkedBag<std::string> copy(original);
    copy.remove("a");
    CHECK(original.contains("a"));
    CHECK(!copy.contains("a"));

    h235::LinkedBag<std::string> assigned;
    assigned = original;
    original.clear();
    CHECK_EQ(assigned.getCurrentSize(), 2);
}
