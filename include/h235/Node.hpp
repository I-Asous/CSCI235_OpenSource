#pragma once

namespace h235 {

/**
 * @brief A singly linked node holding one item.
 * @tparam T The type of item stored in the node.
 *
 * @note Shared by every linked ADT in the library.
 */
template <class T>
class Node {
public:
    /**
     * @brief Creates a node with a default-constructed item and no next node.
     */
    Node() = default;

    /**
     * @brief Creates a node holding an item.
     * @param item The item to store.
     * @param next The node that follows this one, or nullptr if there is none.
     */
    explicit Node(const T& item, Node* next = nullptr) : item_(item), next_(next) {}

    /**
     * @brief Gets the item stored in the node.
     * @return A const reference to the item.
     */
    const T& getItem() const { return item_; }

    /**
     * @brief Gets the item stored in the node.
     * @return A (non-const) reference to the item, so it can be changed in place.
     */
    T& getItem() { return item_; }

    /**
     * @brief Replaces the item stored in the node.
     * @param item The new item to store.
     */
    void setItem(const T& item) { item_ = item; }

    /**
     * @brief Gets the node that follows this one.
     * @return A pointer to the next node, or nullptr if this is the last node.
     */
    Node* getNext() const { return next_; }

    /**
     * @brief Links this node to the node that should follow it.
     * @param next The new next node, or nullptr to make this the last node.
     */
    void setNext(Node* next) { next_ = next; }

private:
    T item_{};
    Node* next_ = nullptr;
};

}  // namespace h235
