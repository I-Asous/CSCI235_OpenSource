#pragma once

#include <vector>

namespace h235 {

/**
 * @brief An unordered collection that allows duplicates.
 * @tparam T The type of item stored in the bag.
 */
template <class T>
class BagInterface {
public:
    virtual ~BagInterface() = default;

    /**
     * @brief Gets the number of items currently in the bag.
     * @return The number of items, counting duplicates.
     */
    virtual int getCurrentSize() const = 0;

    /**
     * @brief Checks whether the bag holds no items.
     * @return True if the bag is empty, false otherwise.
     */
    virtual bool isEmpty() const = 0;

    /**
     * @brief Adds a new entry to the bag.
     * @param newEntry The item to add.
     * @return True if the item was added, false if the bag had no room.
     */
    virtual bool add(const T& newEntry) = 0;

    /**
     * @brief Removes one occurrence of an entry from the bag.
     * @param anEntry The item to remove.
     * @return True if an occurrence was removed, false if it was not in the bag.
     */
    virtual bool remove(const T& anEntry) = 0;

    /**
     * @brief Removes every item from the bag.
     */
    virtual void clear() = 0;

    /**
     * @brief Counts how many times an entry appears in the bag.
     * @param anEntry The item to count.
     * @return The number of occurrences of anEntry.
     */
    virtual int getFrequencyOf(const T& anEntry) const = 0;

    /**
     * @brief Checks whether the bag holds at least one occurrence of an entry.
     * @param anEntry The item to look for.
     * @return True if anEntry is in the bag, false otherwise.
     */
    virtual bool contains(const T& anEntry) const = 0;

    /**
     * @brief Copies every item in the bag into a vector.
     * @return A vector holding all items, in no particular order.
     */
    virtual std::vector<T> toVector() const = 0;
};

}  // namespace h235
