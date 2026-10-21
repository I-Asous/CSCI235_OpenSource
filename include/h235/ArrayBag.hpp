#pragma once

#include <vector>

#include "h235/BagInterface.hpp"

namespace h235 {

/**
 * @brief A fixed-capacity bag backed by a plain array.
 * @tparam T The type of item stored in the bag.
 *
 * @note The bag holds at most DEFAULT_CAPACITY items. Once it is full,
 * add() returns false instead of growing.
 */
template <class T>
class ArrayBag : public BagInterface<T> {
public:
    static constexpr int DEFAULT_CAPACITY = 64;

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
     * @brief Adds a new entry to the end of the array.
     * @param newEntry The item to add.
     * @return True if the item was added, false if the bag is already full.
     */
    bool add(const T& newEntry) override {
        if (itemCount_ >= DEFAULT_CAPACITY) {
            return false;
        }
        items_[itemCount_++] = newEntry;
        return true;
    }

    /**
     * @brief Removes one occurrence of an entry from the bag.
     * @param anEntry The item to remove.
     * @return True if an occurrence was removed, false if it was not in the bag.
     *
     * @note The last item is moved into the removed item's slot,
     * so the order of the remaining items may change.
     */
    bool remove(const T& anEntry) override {
        int index = getIndexOf(anEntry);
        if (index < 0) {
            return false;
        }
        // Order does not matter in a bag, so fill the gap with the last item.
        items_[index] = items_[--itemCount_];
        return true;
    }

    /**
     * @brief Removes every item from the bag.
     */
    void clear() override { itemCount_ = 0; }

    /**
     * @brief Counts how many times an entry appears in the bag.
     * @param anEntry The item to count.
     * @return The number of occurrences of anEntry.
     */
    int getFrequencyOf(const T& anEntry) const override {
        int frequency = 0;
        for (int i = 0; i < itemCount_; ++i) {
            if (items_[i] == anEntry) {
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
    bool contains(const T& anEntry) const override { return getIndexOf(anEntry) >= 0; }

    /**
     * @brief Copies every item in the bag into a vector.
     * @return A vector holding all items, in array order.
     */
    std::vector<T> toVector() const override {
        return std::vector<T>(items_, items_ + itemCount_);
    }

private:
    /**
     * @brief Finds the array index of the first occurrence of an item.
     * @param target The item to look for.
     * @return The index of target, or -1 if it is not in the bag.
     */
    int getIndexOf(const T& target) const {
        for (int i = 0; i < itemCount_; ++i) {
            if (items_[i] == target) {
                return i;
            }
        }
        return -1;
    }

    T items_[DEFAULT_CAPACITY]{};
    int itemCount_ = 0;
};

}  // namespace h235
