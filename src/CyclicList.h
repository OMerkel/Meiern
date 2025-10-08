#pragma once
#include <list>
#include <iterator>

// A cyclic list wrapper for std::list
// Calling next() on the last element returns the first, and prev() on the first returns the last.
template <typename T>
class CyclicList {
public:
    using iterator = typename std::list<T>::iterator;
    using const_iterator = typename std::list<T>::const_iterator;

    void push_back(const T& value) { data_.push_back(value); }
    void push_front(const T& value) { data_.push_front(value); }
    void clear() { data_.clear(); }
    bool empty() const { return data_.empty(); }
    iterator erase(const_iterator it) { return data_.erase(it); }
    size_t size() const { return data_.size(); }
    iterator begin() { return data_.begin(); }
    iterator end() { return data_.end(); }
    const_iterator begin() const { return data_.begin(); }
    const_iterator end() const { return data_.end(); }

    // Returns the next iterator, wrapping to begin() if at end
    iterator next(iterator it) {
        if (data_.empty()) return data_.end();
        auto next_it = std::next(it);
        return (next_it == data_.end()) ? data_.begin() : next_it;
    }

    // Returns the previous iterator, wrapping to last if at begin
    iterator prev(iterator it) {
        if (data_.empty()) return data_.end();
        return (it == data_.begin()) ? std::prev(data_.end()) : std::prev(it);
    }

    // Access to underlying list
    std::list<T>& data() { return data_; }
    const std::list<T>& data() const { return data_; }

private:
    std::list<T> data_;
};
