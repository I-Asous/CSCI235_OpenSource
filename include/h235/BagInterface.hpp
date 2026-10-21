#pragma once

#include <vector>

namespace h235 {

/// An unordered collection that allows duplicates.
template <class T>
class BagInterface {
public:
    virtual ~BagInterface() = default;

    virtual int getCurrentSize() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool add(const T& newEntry) = 0;
    /// Removes one occurrence of anEntry. Returns false if it was not in the bag.
    virtual bool remove(const T& anEntry) = 0;
    virtual void clear() = 0;
    virtual int getFrequencyOf(const T& anEntry) const = 0;
    virtual bool contains(const T& anEntry) const = 0;
    virtual std::vector<T> toVector() const = 0;
};

}  // namespace h235
