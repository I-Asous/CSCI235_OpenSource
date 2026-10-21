#pragma once

#include <vector>

#include "h235/BagInterface.hpp"

namespace h235 {

/// A fixed-capacity bag backed by a plain array.
template <class T>
class ArrayBag : public BagInterface<T> {
public:
    static constexpr int DEFAULT_CAPACITY = 64;

    int getCurrentSize() const override { return itemCount_; }
    bool isEmpty() const override { return itemCount_ == 0; }

    bool add(const T& newEntry) override {
        if (itemCount_ >= DEFAULT_CAPACITY) {
            return false;
        }
        items_[itemCount_++] = newEntry;
        return true;
    }

    bool remove(const T& anEntry) override {
        int index = getIndexOf(anEntry);
        if (index < 0) {
            return false;
        }
        // Order does not matter in a bag, so fill the gap with the last item.
        items_[index] = items_[--itemCount_];
        return true;
    }

    void clear() override { itemCount_ = 0; }

    int getFrequencyOf(const T& anEntry) const override {
        int frequency = 0;
        for (int i = 0; i < itemCount_; ++i) {
            if (items_[i] == anEntry) {
                ++frequency;
            }
        }
        return frequency;
    }

    bool contains(const T& anEntry) const override { return getIndexOf(anEntry) >= 0; }

    std::vector<T> toVector() const override {
        return std::vector<T>(items_, items_ + itemCount_);
    }

private:
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
