#pragma once

#include <stdexcept>
#include <utility>

#include "h235/Node.hpp"

namespace h235 {

/// A first-in, first-out queue backed by a chain of nodes with head and tail pointers.
template <class T>
class LinkedQueue {
public:
    LinkedQueue() = default;

    LinkedQueue(const LinkedQueue& other) {
        for (Node<T>* cur = other.front_; cur != nullptr; cur = cur->getNext()) {
            enqueue(cur->getItem());
        }
    }

    LinkedQueue& operator=(LinkedQueue other) {
        std::swap(front_, other.front_);
        std::swap(back_, other.back_);
        std::swap(size_, other.size_);
        return *this;
    }

    ~LinkedQueue() {
        while (dequeue()) {
        }
    }

    bool isEmpty() const { return front_ == nullptr; }
    int size() const { return size_; }

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

    /// Removes the front item. Returns false if the queue was empty.
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

    /// Throws std::logic_error if the queue is empty.
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
