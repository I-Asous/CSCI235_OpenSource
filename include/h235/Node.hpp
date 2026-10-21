#pragma once

namespace h235 {

/// A singly linked node holding one item. Shared by every linked ADT in the library.
template <class T>
class Node {
public:
    Node() = default;
    explicit Node(const T& item, Node* next = nullptr) : item_(item), next_(next) {}

    const T& getItem() const { return item_; }
    T& getItem() { return item_; }
    void setItem(const T& item) { item_ = item; }

    Node* getNext() const { return next_; }
    void setNext(Node* next) { next_ = next; }

private:
    T item_{};
    Node* next_ = nullptr;
};

}  // namespace h235
