#pragma once

#include <stdexcept>
#include <utility>

#include "h235/Node.hpp"

namespace h235 {

/**
 * @brief A first-in, first-out queue backed by a chain of nodes
 * with front and back pointers.
 * @tparam T The type of item stored in the queue.
 */
template <class T>
class LinkedQueue {
public:
    /**
     * @brief Creates an empty queue.
     */
    LinkedQueue() = default;

    /**
     * @brief Creates a deep copy of another queue.
     * @param other The queue to copy.
     */
    LinkedQueue(const LinkedQueue& other) {
        for (Node<T>* cur = other.front_; cur != nullptr; cur = cur->getNext()) {
            enqueue(cur->getItem());
        }
    }

    /**
     * @brief Replaces this queue's contents with a copy of another queue.
     * @param other The queue to copy, taken by value (copy-and-swap).
     * @return A reference to this queue.
     */
    LinkedQueue& operator=(LinkedQueue other) {
        std::swap(front_, other.front_);
        std::swap(back_, other.back_);
        std::swap(size_, other.size_);
        return *this;
    }

    /**
     * @brief Deletes every node in the chain.
     */
    ~LinkedQueue() {
        while (dequeue()) {
        }
    }

    /**
     * @brief Checks whether the queue holds no items.
     * @return True if the queue is empty, false otherwise.
     */
    bool isEmpty() const { return front_ == nullptr; }

    /**
     * @brief Gets the number of items in the queue.
     * @return The number of items.
     */
    int size() const { return size_; }

    /**
     * @brief Adds an item to the back of the queue.
     * @param newEntry The item to add.
     */
    void enqueue(const T& newEntry) {
        auto* node = new Node<T>(newEntry);
        if (isEmpty()) {
            front_ = node;
        } else {
            back_->setNext(node);
        }
        back_ = node;
        ++size_;
    }

    /**
     * @brief Removes the item at the front of the queue.
     * @return True if an item was removed, false if the queue was empty.
     */
    bool dequeue() {
        if (isEmpty()) {
            return false;
        }
        Node<T>* oldFront = front_;
        front_ = front_->getNext();
        if (front_ == nullptr) {
            back_ = nullptr;
        }
        delete oldFront;
        --size_;
        return true;
    }

    /**
     * @brief Gets the item at the front of the queue without removing it.
     * @return A const reference to the front item.
     * @throws std::logic_error If the queue is empty.
     */
    const T& peekFront() const {
        if (isEmpty()) {
            throw std::logic_error("peekFront() called on an empty queue");
        }
        return front_->getItem();
    }

private:
    Node<T>* front_ = nullptr;
    Node<T>* back_ = nullptr;
    int size_ = 0;
};

}  // namespace h235
