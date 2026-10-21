#pragma once

#include <stdexcept>
#include <utility>

#include "h235/Node.hpp"

namespace h235 {

/// A last-in, first-out stack backed by a chain of nodes. The top is the head.
template <class T>
class LinkedStack {
public:
    LinkedStack() = default;

    LinkedStack(const LinkedStack& other) {
        Node<T>* tail = nullptr;
        for (Node<T>* cur = other.top_; cur != nullptr; cur = cur->getNext()) {
            auto* node = new Node<T>(cur->getItem());
            if (tail == nullptr) {
                top_ = node;
            } else {
                tail->setNext(node);
            }
            tail = node;
        }
        size_ = other.size_;
    }

    LinkedStack& operator=(LinkedStack other) {
        std::swap(top_, other.top_);
        std::swap(size_, other.size_);
        return *this;
    }

    ~LinkedStack() {
        while (pop()) {
        }
    }

    bool isEmpty() const { return top_ == nullptr; }
    int size() const { return size_; }

    void push(const T& newEntry) {
        top_ = new Node<T>(newEntry, top_);
        ++size_;
    }

    /// Removes the top item. Returns false if the stack was empty.
    bool pop() {
        if (isEmpty()) {
            return false;
        }
        Node<T>* oldTop = top_;
        top_ = top_->getNext();
        delete oldTop;
        --size_;
        return true;
    }

    /// Throws std::logic_error if the stack is empty.
    const T& peek() const {
        if (isEmpty()) {
            throw std::logic_error("peek() called on an empty stack");
        }
        return top_->getItem();
    }

private:
    Node<T>* top_ = nullptr;
    int size_ = 0;
};

}  // namespace h235
