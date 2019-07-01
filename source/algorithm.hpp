#ifndef BUW_ALGORITHM_HPP
#define BUW_ALGORITHM_HPP

#include "point.hpp"
#include "segment.hpp"
#include "set.hpp"
#include "event.hpp"
#include "utils.hpp"

#include <vector>

struct lessEventX {
  bool operator() (Event const& lhs, Event const& rhs) const {
    return lhs.point.x < rhs.point.x;
  }
};

std::vector<Point> bentleyOttmannIntersections(std::vector<Segment> const& segments)
{
  Set<Event, lessEventX> events;
  for(Segment const& segment : segments) {
    if(segment.a.x < segment.b.x) {
      events.insert({ "open", segment.a, segment });
      events.insert({ "close", segment.b, segment });
    } else {
      events.insert({ "open", segment.b, segment });
      events.insert({ "close", segment.a, segment });
    }
  }



  std::vector<Segment> openSegments;
  std::vector<Point> intersections;

  while (events.size() > 0) {
    // get and erase first element in events
    Event event = events.pop_front();

    Segment segment = event.s1;
    float lineX = event.point.x;
    Segment sweepLine{
      {lineX, 0},
      {lineX, 1}
    };

    /*
     * First case: A new segment begins
     */
    if(event.type == "open") {
      // open segment
      openSegments.push_back(segment);

      // sort after insertion by point of intersection with sweepline
      buw::mergesort(std::begin(openSegments), std::end(openSegments), 
        [&sweepLine](Segment const& lhs, Segment const& rhs) {
          float y1 = intersectLine(sweepLine, lhs).second.y;
          float y2 = intersectLine(sweepLine, rhs).second.y;
          return y1 < y2;
        }
      );

      auto it = std::find(std::cbegin(openSegments), std::cend(openSegments), segment);
      auto prev = it - 1;
      auto next = it + 1;

      // if there is a previous segment
      if(prev != (std::cbegin(openSegments) - 1)) {
        std::pair<bool, Point> result = intersectSegment(segment, *prev);
        if(result.first) {
          events.insert({"intersection", result.second, *prev, segment});
        }
      }

      // if there is a next segment
      if(next != (std::cend(openSegments))) {
        std::pair<bool, Point> result = intersectSegment(segment, *next);
        if(result.first) {
          events.insert({"intersection", result.second, segment, *next});
        }
      }

    }
    /*
     * Second case: A segment ends.
     */
    else if(event.type == "close") {
      auto it = std::find(std::cbegin(openSegments), std::cend(openSegments), segment);
      auto prev = it - 1;
      auto next = it + 1;

      // if there is a previous and a next segment
      if(prev != (std::cbegin(openSegments) - 1) && next != (std::cend(openSegments))) {
        std::pair<bool, Point> result = intersectSegment(*prev, *next);
        if(result.first && result.second.x >= lineX) {
          events.insert({"intersection", result.second, *prev, *next});
        }
      }

      // close segment
      openSegments.erase(it);
    }
    /*
     * Third case: An intersection.
     */
    else { // event.type == "intersection"
      intersections.push_back(event.point);

      auto it1 = std::find(std::begin(openSegments), std::end(openSegments), event.s1);
      auto it2 = std::find(std::begin(openSegments), std::end(openSegments), event.s2);
      auto next = it1 - 1;
      auto prev = it2 + 1;

      std::iter_swap(it1, it2);

      if(next != (std::begin(openSegments) - 1)) {
        std::pair<bool, Point> result = intersectSegment(event.s2, *next);
        if(result.first && result.second.x > lineX) {
          events.insert({"intersection", result.second, *next, event.s2});
        }
      }

      if(prev != (std::end(openSegments))) {
        std::pair<bool, Point> result = intersectSegment(*prev, event.s1);
        if(result.first && result.second.x > lineX) {
          events.insert({"intersection", result.second, event.s1, *prev});
        }
      }
    }
  }

  return intersections;
}


std::vector<Point> bruteForceIntersections(std::vector<Segment> const& segments)
{
  std::vector<Point> intersections;

  for(auto it1 = std::cbegin(segments); it1 != std::cend(segments); it1++) {
    for(auto it2{it1}; it2 != std::cend(segments); it2++) {
      if(*it1 == *it2) {
        continue;
      }

      auto result = intersectSegment(*it1, *it2);
      if(result.first) {
        intersections.push_back(result.second);
      }
    }
  }

  return intersections;
}

#endif
