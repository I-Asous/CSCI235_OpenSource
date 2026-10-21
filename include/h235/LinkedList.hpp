#pragma once

#include <stdexcept>
#include <utility>
#include <vector>

#include "h235/Node.hpp"

namespace h235 {

/// A positional list backed by a chain of nodes. Positions are 1-based, as in the textbook.
template <class T>
class LinkedList {
public:
    LinkedList() = default;

    LinkedList(const LinkedList& other) {
        int position = 1;
        for (Node<T>* cur = other.head_; cur != nullptr; cur = cur->getNext()) {
            insert(position++, cur->getItem());
        }
    }

    LinkedList& operator=(LinkedList other) {
        std::swap(head_, other.head_);
        std::swap(length_, other.length_);
        return *this;
    }

    ~LinkedList() { clear(); }

    bool isEmpty() const { return length_ == 0; }
    int getLength() const { return length_; }

    /// Inserts newEntry so that it ends up at newPosition (1 <= newPosition <= length + 1).
    /// Returns false if the position is out of range.
    bool insert(int newPosition, const T& newEntry) {
        if (newPosition < 1 || newPosition > length_ + 1) {
            return false;
        }
        if (newPosition == 1) {
            head_ = new Node<T>(newEntry, head_);
        } else {
            Node<T>* prev = getNodeAt(newPosition - 1);
            prev->setNext(new Node<T>(newEntry, prev->getNext()));
        }
        ++length_;
        return true;
    }

    /// Removes the entry at position. Returns false if the position is out of range.
    bool remove(int position) {
        if (position < 1 || position > length_) {
            return false;
        }
        Node<T>* doomed;
        if (position == 1) {
            doomed = head_;
            head_ = head_->getNext();
        } else {
            Node<T>* prev = getNodeAt(position - 1);
            doomed = prev->getNext();
            prev->setNext(doomed->getNext());
        }
        delete doomed;
        --length_;
        return true;
    }

    void clear() {
        while (remove(1)) {
        }
    }

    /// Throws std::out_of_range if position is not in [1, length].
    const T& getEntry(int position) const {
        checkPosition(position);
        return getNodeAt(position)->getItem();
    }

    /// Throws std::out_of_range if position is not in [1, length].
    void replace(int position, const T& newEntry) {
        checkPosition(position);
        getNodeAt(position)->setItem(newEntry);
    }

    std::vector<T> toVector() const {
        std::vector<T> result;
        result.reserve(length_);
        for (Node<T>* cur = head_; cur != nullptr; cur = cur->getNext()) {
            result.push_back(cur->getItem());
        }
        return result;
    }

private:
    void checkPosition(int position) const {
        if (position < 1 || position > length_) {
            throw std::out_of_range("LinkedList position out of range");
        }
    }

    Node<T>* getNodeAt(int position) const {
        Node<T>* cur = head_;
        for (int i = 1; i < position; ++i) {
            cur = cur->getNext();
        }
        return cur;
    }

    Node<T>* head_ = nullptr;
    int length_ = 0;
};

}  // namespace h235
