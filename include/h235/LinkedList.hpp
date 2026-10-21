#pragma once

#include <stdexcept>
#include <utility>
#include <vector>

#include "h235/Node.hpp"

namespace h235 {

/**
 * @brief A positional list backed by a chain of nodes.
 * @tparam T The type of item stored in the list.
 *
 * @note Positions are 1-based, as in the textbook.
 */
template <class T>
class LinkedList {
public:
    /**
     * @brief Creates an empty list.
     */
    LinkedList() = default;

    /**
     * @brief Creates a deep copy of another list.
     * @param other The list to copy.
     */
    LinkedList(const LinkedList& other) {
        int position = 1;
        for (Node<T>* cur = other.head_; cur != nullptr; cur = cur->getNext()) {
            insert(position++, cur->getItem());
        }
    }

    /**
     * @brief Replaces this list's contents with a copy of another list.
     * @param other The list to copy, taken by value (copy-and-swap).
     * @return A reference to this list.
     */
    LinkedList& operator=(LinkedList other) {
        std::swap(head_, other.head_);
        std::swap(length_, other.length_);
        return *this;
    }

    /**
     * @brief Deletes every node in the chain.
     */
    ~LinkedList() { clear(); }

    /**
     * @brief Checks whether the list holds no entries.
     * @return True if the list is empty, false otherwise.
     */
    bool isEmpty() const { return length_ == 0; }

    /**
     * @brief Gets the number of entries in the list.
     * @return The length of the list.
     */
    int getLength() const { return length_; }

    /**
     * @brief Inserts an entry so that it ends up at the given position.
     * @param newPosition The position for the new entry (1 <= newPosition <= length + 1).
     * @param newEntry The item to insert.
     * @return True if the entry was inserted, false if the position is out of range.
     */
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

    /**
     * @brief Removes the entry at the given position.
     * @param position The position of the entry to remove (1 <= position <= length).
     * @return True if the entry was removed, false if the position is out of range.
     */
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

    /**
     * @brief Removes every entry from the list and deletes all nodes.
     */
    void clear() {
        while (remove(1)) {
        }
    }

    /**
     * @brief Gets the entry at the given position.
     * @param position The position of the entry (1 <= position <= length).
     * @return A const reference to the entry at position.
     * @throws std::out_of_range If position is not in [1, length].
     */
    const T& getEntry(int position) const {
        checkPosition(position);
        return getNodeAt(position)->getItem();
    }

    /**
     * @brief Replaces the entry at the given position.
     * @param position The position of the entry to replace (1 <= position <= length).
     * @param newEntry The item to store at position.
     * @throws std::out_of_range If position is not in [1, length].
     */
    void replace(int position, const T& newEntry) {
        checkPosition(position);
        getNodeAt(position)->setItem(newEntry);
    }

    /**
     * @brief Copies every entry in the list into a vector.
     * @return A vector holding all entries, in list order.
     */
    std::vector<T> toVector() const {
        std::vector<T> result;
        result.reserve(length_);
        for (Node<T>* cur = head_; cur != nullptr; cur = cur->getNext()) {
            result.push_back(cur->getItem());
        }
        return result;
    }

private:
    /**
     * @brief Verifies that a position refers to an existing entry.
     * @param position The position to check.
     * @throws std::out_of_range If position is not in [1, length].
     */
    void checkPosition(int position) const {
        if (position < 1 || position > length_) {
            throw std::out_of_range("LinkedList position out of range");
        }
    }

    /**
     * @brief Walks the chain to the node at the given position.
     * @param position The position of the node (1 <= position <= length).
     * @return A pointer to the node at position.
     *
     * @note This helper does not check the range. Callers must
     * validate position before calling it.
     */
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
