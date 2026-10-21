#include <stdexcept>
#include <vector>

#include "framework.hpp"
#include "h235/LinkedList.hpp"

TEST_CASE("LinkedList: insert at front, middle, and end") {
    h235::LinkedList<int> list;
    CHECK(list.insert(1, 2));
    CHECK(list.insert(1, 1));
    CHECK(list.insert(3, 4));
    CHECK(list.insert(3, 3));
    CHECK_EQ(list.toVector(), (std::vector<int>{1, 2, 3, 4}));
}

TEST_CASE("LinkedList: rejects out-of-range positions") {
    h235::LinkedList<int> list;
    CHECK(!list.insert(0, 1));
    CHECK(!list.insert(2, 1));
    CHECK(!list.remove(1));
    CHECK_THROWS(list.getEntry(1), std::out_of_range);
    CHECK_THROWS(list.replace(1, 9), std::out_of_range);
}

TEST_CASE("LinkedList: remove and replace") {
    h235::LinkedList<char> list;
    list.insert(1, 'a');
    list.insert(2, 'b');
    list.insert(3, 'c');
    CHECK(list.remove(2));
    CHECK_EQ(list.getEntry(2), 'c');
    list.replace(1, 'z');
    CHECK_EQ(list.toVector(), (std::vector<char>{'z', 'c'}));
    list.clear();
    CHECK(list.isEmpty());
}

TEST_CASE("LinkedList: copy is independent of original") {
    h235::LinkedList<int> list;
    list.insert(1, 10);
    list.insert(2, 20);
    h235::LinkedList<int> copy(list);
    list.replace(1, 99);
    CHECK_EQ(copy.getEntry(1), 10);
    CHECK_EQ(copy.getLength(), 2);
}
