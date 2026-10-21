#pragma once

#include <utility>
#include <vector>

#include "h235/BagInterface.hpp"
#include "h235/Node.hpp"

namespace h235 {

/**
 * @brief An unbounded bag backed by a chain of nodes.
 * @tparam T The type of item stored in the bag.
 */
template <class T>
class LinkedBag : public BagInterface<T> {
public:
    /**
     * @brief Creates an empty bag.
     */
    LinkedBag() = default;

    /**
     * @brief Creates a deep copy of another bag.
     * @param other The bag to copy.
     *
     * @note The copy gets its own nodes and keeps the same item order as other.
     */
    LinkedBag(const LinkedBag& other) {
        // Walk the other chain and append, so the copy keeps the same order.
        Node<T>* tail = nullptr;
        for (Node<T>* cur = other.head_; cur != nullptr; cur = cur->getNext()) {
            auto* node = new Node<T>(cur->getItem());
            if (tail == nullptr) {
                head_ = node;
            } else {
                tail->setNext(node);
            }
            tail = node;
        }
        itemCount_ = other.itemCount_;
    }

    /**
     * @brief Replaces this bag's contents with a copy of another bag.
     * @param other The bag to copy, taken by value (copy-and-swap).
     * @return A reference to this bag.
     */
    LinkedBag& operator=(LinkedBag other) {
        std::swap(head_, other.head_);
        std::swap(itemCount_, other.itemCount_);
        return *this;
    }

    /**
     * @brief Deletes every node in the chain.
     */
    ~LinkedBag() override { clear(); }

    /**
     * @brief Gets the number of items currently in the bag.
     * @return The number of items, counting duplicates.
     */
    int getCurrentSize() const override { return itemCount_; }

    /**
     * @brief Checks whether the bag holds no items.
     * @return True if the bag is empty, false otherwise.
     */
    bool isEmpty() const override { return itemCount_ == 0; }

    /**
     * @brief Adds a new entry at the front of the chain.
     * @param newEntry The item to add.
     * @return Always true, since a linked bag never runs out of room.
     */
    bool add(const T& newEntry) override {
        head_ = new Node<T>(newEntry, head_);
        ++itemCount_;
        return true;
    }

    /**
     * @brief Removes one occurrence of an entry from the bag.
     * @param anEntry The item to remove.
     * @return True if an occurrence was removed, false if it was not in the bag.
     *
     * @note The head's item is copied into the target node and the head is
     * deleted instead, so no previous-node pointer is needed.
     */
    bool remove(const T& anEntry) override {
        Node<T>* target = getPointerTo(anEntry);
        if (target == nullptr) {
            return false;
        }
        // Copy the head's item into the target, then delete the head.
        target->setItem(head_->getItem());
        Node<T>* oldHead = head_;
        head_ = head_->getNext();
        delete oldHead;
        --itemCount_;
        return true;
    }

    /**
     * @brief Removes every item from the bag and deletes all nodes.
     */
    void clear() override {
        while (head_ != nullptr) {
            Node<T>* next = head_->getNext();
            delete head_;
            head_ = next;
        }
        itemCount_ = 0;
    }

    /**
     * @brief Counts how many times an entry appears in the bag.
     * @param anEntry The item to count.
     * @return The number of occurrences of anEntry.
     */
    int getFrequencyOf(const T& anEntry) const override {
        int frequency = 0;
        for (Node<T>* cur = head_; cur != nullptr; cur = cur->getNext()) {
            if (cur->getItem() == anEntry) {
                ++frequency;
            }
        }
        return frequency;
    }

    /**
     * @brief Checks whether the bag holds at least one occurrence of an entry.
     * @param anEntry The item to look for.
     * @return True if anEntry is in the bag, false otherwise.
     */
    bool contains(const T& anEntry) const override { return getPointerTo(anEntry) != nullptr; }

    /**
     * @brief Copies every item in the bag into a vector.
     * @return A vector holding all items, in chain order (most recently added first).
     */
    std::vector<T> toVector() const override {
        std::vector<T> result;
        result.reserve(itemCount_);
        for (Node<T>* cur = head_; cur != nullptr; cur = cur->getNext()) {
            result.push_back(cur->getItem());
        }
        return result;
    }

private:
    /**
     * @brief Finds the node holding the first occurrence of an item.
     * @param target The item to look for.
     * @return A pointer to the node holding target, or nullptr if it is not in the bag.
     */
    Node<T>* getPointerTo(const T& target) const {
        for (Node<T>* cur = head_; cur != nullptr; cur = cur->getNext()) {
            if (cur->getItem() == target) {
                return cur;
            }
        }
        return nullptr;
    }

    Node<T>* head_ = nullptr;
    int itemCount_ = 0;
};

}  // namespace h235
