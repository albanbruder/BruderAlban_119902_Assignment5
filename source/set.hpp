#ifndef BUW_SET_HPP
#define BUW_SET_HPP

#include <vector>
#include <iterator>
#include "mergesort.hpp"

/**
 * A set with unique and sorted values.
 */
template <typename T, typename Comparator = std::less<T>>
class Set {
  using InputIterator = std::iterator<std::input_iterator_tag, T>;

  public:
    /**
     * Initialize an empty set.
     */
    Set() {};

    /**
     * Initialize a set by copying from the given iterators.
     */
    Set(InputIterator const& first, InputIterator const& last)
      : elements_(first, last)
    {
      // sort the elements
      buw::mergesort(std::begin(elements_), std::end(elements_), Comparator());
    };

    /**
     * Insert a value into the set
     */
    void insert(T const& value) {
      // check if the element is already in the set
      auto it = std::find(std::cbegin(elements_), std::cend(elements_), value);
      if(it == std::cend(elements_)) {
        // insert & sort
        elements_.push_back(value);
        buw::mergesort(std::begin(elements_), std::end(elements_), Comparator());
      }
    }

    /**
     * Get the first element in the set.
     */
    T front() {
      return elements_.front();
    }

    /**
     * Get the last element in the set.
     */
    T back() {
      return elements_.back();
    }

    /**
     * Remove and return the first element in the set.
     */
    T pop_front() {
      T tmp = front();
      elements_.erase(std::begin(elements_));
      return tmp;
    }

    /**
     * Remove and return the last element in the set.
     */
    T pop_back() {
      T tmp = back();
      elements_.pop_back();
      return tmp;
    }

    /**
     * Return the vector of elements.
     */
    std::vector<T> toVector() const {
      return elements_;
    }

    /**
     * The number of elements in the set.
     */
    std::size_t size() const {
      return elements_.size();
    }

    /** Check if an element has a predecessor. */
    bool hasPrevious(T const& value) {
      auto it = std::find(std::cbegin(elements_), std::cend(elements_), value) - 1;
      return (it != (std::cbegin(elements_) - 1));
    }

    /**
     * Get the predecessor of an element.
     */
    T previous(T const& value) {
      auto it = std::find(std::cbegin(elements_), std::cend(elements_), value) - 1;
      return *it;
    }

    /**
     * Check if an element has a successor.
     */
    bool hasNext(T const& value) {
      auto it = std::find(std::cbegin(elements_), std::cend(elements_), value) + 1;
      return (it != std::cend(elements_));
    }

    /**
     * Get the successor of an element.
     */
    T next(T const& value) {
      auto it = std::find(std::cbegin(elements_), std::cend(elements_), value) + 1;
      return *it;
    }

    /**
     * Swap positions of 2 elements.
     */
    void swap(T const& v1, T const& v2) {
      auto it1 = std::find(std::cbegin(elements_), std::cend(elements_), v1);
      auto it2 = std::find(std::cbegin(elements_), std::cend(elements_), v2);
      std::iter_swap(it1, it2);
    }

  private:
    std::vector<T> elements_;

};

#endif