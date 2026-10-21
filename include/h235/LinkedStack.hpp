#pragma once

#include <stdexcept>
#include <utility>

#include "h235/Node.hpp"

namespace h235 {

/**
 * @brief A last-in, first-out stack backed by a chain of nodes.
 * @tparam T The type of item stored in the stack.
 *
 * @note The top of the stack is the head of the chain.
 */
template <class T>
class LinkedStack {
public:
    /**
     * @brief Creates an empty stack.
     */
    LinkedStack() = default;

    /**
     * @brief Creates a deep copy of another stack.
     * @param other The stack to copy.
     *
     * @note Nodes are appended in order, so the copy has the same top as other.
     */
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

    /**
     * @brief Replaces this stack's contents with a copy of another stack.
     * @param other The stack to copy, taken by value (copy-and-swap).
     * @return A reference to this stack.
     */
    LinkedStack& operator=(LinkedStack other) {
        std::swap(top_, other.top_);
        std::swap(size_, other.size_);
        return *this;
    }

    /**
     * @brief Deletes every node in the chain.
     */
    ~LinkedStack() {
        while (pop()) {
        }
    }

    /**
     * @brief Checks whether the stack holds no items.
     * @return True if the stack is empty, false otherwise.
     */
    bool isEmpty() const { return top_ == nullptr; }

    /**
     * @brief Gets the number of items on the stack.
     * @return The number of items.
     */
    int size() const { return size_; }

    /**
     * @brief Pushes an item onto the top of the stack.
     * @param newEntry The item to push.
     */
    void push(const T& newEntry) {
        top_ = new Node<T>(newEntry, top_);
        ++size_;
    }

    /**
     * @brief Removes the item at the top of the stack.
     * @return True if an item was removed, false if the stack was empty.
     */
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

    /**
     * @brief Gets the item at the top of the stack without removing it.
     * @return A const reference to the top item.
     * @throws std::logic_error If the stack is empty.
     */
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
