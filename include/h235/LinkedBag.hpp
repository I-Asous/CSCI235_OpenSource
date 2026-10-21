#pragma once

#include <utility>
#include <vector>

#include "h235/BagInterface.hpp"
#include "h235/Node.hpp"

namespace h235 {

/// An unbounded bag backed by a chain of nodes.
template <class T>
class LinkedBag : public BagInterface<T> {
public:
    LinkedBag() = default;

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

    LinkedBag& operator=(LinkedBag other) {
        std::swap(head_, other.head_);
        std::swap(itemCount_, other.itemCount_);
        return *this;
    }

    ~LinkedBag() override { clear(); }

    int getCurrentSize() const override { return itemCount_; }
    bool isEmpty() const override { return itemCount_ == 0; }

    bool add(const T& newEntry) override {
        head_ = new Node<T>(newEntry, head_);
        ++itemCount_;
        return true;
    }

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

    void clear() override {
        while (head_ != nullptr) {
            Node<T>* next = head_->getNext();
            delete head_;
            head_ = next;
        }
        itemCount_ = 0;
    }

    int getFrequencyOf(const T& anEntry) const override {
        int frequency = 0;
        for (Node<T>* cur = head_; cur != nullptr; cur = cur->getNext()) {
            if (cur->getItem() == anEntry) {
                ++frequency;
            }
        }
        return frequency;
    }

    bool contains(const T& anEntry) const override { return getPointerTo(anEntry) != nullptr; }

    std::vector<T> toVector() const override {
        std::vector<T> result;
        result.reserve(itemCount_);
        for (Node<T>* cur = head_; cur != nullptr; cur = cur->getNext()) {
            result.push_back(cur->getItem());
        }
        return result;
    }

private:
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
