#include <stdexcept>

#include "framework.hpp"
#include "h235/LinkedQueue.hpp"
#include "h235/LinkedStack.hpp"

TEST_CASE("LinkedStack: last in, first out") {
    h235::LinkedStack<int> s;
    CHECK(s.isEmpty());
    s.push(1);
    s.push(2);
    s.push(3);
    CHECK_EQ(s.size(), 3);
    CHECK_EQ(s.peek(), 3);
    CHECK(s.pop());
    CHECK_EQ(s.peek(), 2);
}

TEST_CASE("LinkedStack: empty stack") {
    h235::LinkedStack<int> s;
    CHECK(!s.pop());
    CHECK_THROWS(s.peek(), std::logic_error);
}

TEST_CASE("LinkedStack: copy preserves order") {
    h235::LinkedStack<int> s;
    s.push(1);
    s.push(2);
    h235::LinkedStack<int> copy = s;
    s.pop();
    CHECK_EQ(copy.peek(), 2);
    copy.pop();
    CHECK_EQ(copy.peek(), 1);
}

TEST_CASE("LinkedQueue: first in, first out") {
    h235::LinkedQueue<int> q;
    CHECK(q.isEmpty());
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    CHECK_EQ(q.size(), 3);
    CHECK_EQ(q.peekFront(), 1);
    CHECK(q.dequeue());
    CHECK_EQ(q.peekFront(), 2);
}

TEST_CASE("LinkedQueue: empty then reuse") {
    h235::LinkedQueue<int> q;
    CHECK(!q.dequeue());
    CHECK_THROWS(q.peekFront(), std::logic_error);
    q.enqueue(5);
    q.dequeue();
    q.enqueue(6);  // back pointer must have been reset when the queue emptied
    CHECK_EQ(q.peekFront(), 6);
}

TEST_CASE("LinkedQueue: assignment is a deep copy") {
    h235::LinkedQueue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    h235::LinkedQueue<int> other;
    other = q;
    q.dequeue();
    CHECK_EQ(other.peekFront(), 1);
    CHECK_EQ(other.size(), 2);
}
