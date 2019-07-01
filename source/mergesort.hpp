#ifndef BUW_MERGESORT_HPP
#define BUW_MERGESORT_HPP

#include <algorithm>
#include <vector>

namespace buw {

  template <typename Iterator, typename Comparator>
  void mergesort(Iterator const& first, Iterator const& last, Comparator const& comp) {
    int d = last - first;
    std::vector<typename Iterator::value_type> tmp;
    
    // only 1 element is in the list
    if(d < 2) {
      return;
    }

    Iterator median = first + d/2;
    mergesort(first, median, comp);
    mergesort(median, last, comp);

    // merge
    Iterator it1{first};
    Iterator it2{median};
    while(it1 != median && it2 != last) {
      if(comp(*it1, *it2)) {
        tmp.push_back(*it1);
        it1++;
      } else {
        tmp.push_back(*it2);
        it2++;
      }
    }

    while(it1 != median) {
      tmp.push_back(*it1);
      it1++;
    }
    while(it2 != last) {
      tmp.push_back(*it2);
      it2++;
    }

    std::move(std::begin(tmp), std::end(tmp), first);
  }

}

#endif