#ifndef BUW_SET_HPP
#define BUW_SET_HPP

#include <vector>
#include <iterator>
#include "mergesort.hpp"

template <typename T, typename Comparator>
class Set {
  using InputIterator = std::iterator<std::input_iterator_tag, T>;

  public:
    Set() {};
    Set(InputIterator const& first, InputIterator const& last)
      : elements_(first, last)
    {
      buw::mergesort(std::begin(elements_), std::end(elements_), Comparator());
    };
    void insert(T const& value) {
      auto it = std::find(std::cbegin(elements_), std::cend(elements_), value);
      if(it == std::cend(elements_)) {
        elements_.push_back(value);
        buw::mergesort(std::begin(elements_), std::end(elements_), Comparator());
      }
    }
    T front() {
      return elements_.front();
    }
    T back() {
      return elements_.back();
    }
    T pop_front() {
      T tmp = front();
      elements_.erase(std::begin(elements_));
      return tmp;
    }
    T pop_back() {
      T tmp = back();
      elements_.pop_back();
      return tmp;
    }

    std::vector<T> toVector() {
      return elements_;
    }

    std::size_t size() const {
      return elements_.size();
    }

    bool hasPrevious(T const& value) {
      auto it = std::find(std::cbegin(elements_), std::cend(elements_), value) - 1;
      return (it != (std::cbegin(elements_) - 1));
    }

    T previous(T const& value) {
      auto it = std::find(std::cbegin(elements_), std::cend(elements_), value) - 1;
      return *it;
    }

    bool hasNext(T const& value) {
      auto it = std::find(std::cbegin(elements_), std::cend(elements_), value) + 1;
      return (it != std::cend(elements_));
    }

    T next(T const& value) {
      auto it = std::find(std::cbegin(elements_), std::cend(elements_), value) + 1;
      return *it;
    }

    void swap(T const& v1, T const& v2) {
      auto it1 = std::find(std::cbegin(elements_), std::cend(elements_), v1);
      auto it2 = std::find(std::cbegin(elements_), std::cend(elements_), v2);
      std::iter_swap(it1, it2);
    }

  private:
    std::vector<T> elements_;

};

#endif