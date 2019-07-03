#ifndef BUW_ALGORITHM_HPP
#define BUW_ALGORITHM_HPP

#include "point.hpp"
#include "line.hpp"
#include "segment.hpp"
#include "set.hpp"
#include "event.hpp"
#include "utils.hpp"

#include <vector>
#include <math.h>
#include <iostream>

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
    Line sweepLine{
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
          float y1 = intersect(sweepLine, lhs).y;
          float y2 = intersect(sweepLine, rhs).y;
          return y1 < y2;
        }
      );

      // if there is a previous segment
      if(hasPrevious(openSegments, segment)) {
        Segment prev = getPrevious(openSegments, segment);

        Point intersection = intersect(segment, prev);
        if(!isinf(intersection.x)) {
          events.insert({"intersection", intersection, prev, segment});
        }
      }

      // if there is a next segment
      if(hasNext(openSegments, segment)) {
        Segment next = getNext(openSegments, segment);

        Point intersection = intersect(segment, next);
        if(!isinf(intersection.x)) {
          events.insert({"intersection", intersection, segment, next});
        }
      }

    }
    /*
     * Second case: A segment ends.
     */
    else if(event.type == "close") {

      // if there is a previous and a next segment
      if(hasPrevious(openSegments, segment) && hasNext(openSegments, segment)) {
        Segment prev = getPrevious(openSegments, segment);
        Segment next = getNext(openSegments, segment);

        Point intersection = intersect(prev, next);
        if(!isinf(intersection.x) && intersection.x >= lineX) {
          events.insert({"intersection", intersection, prev, next});
        }
      }

      // close segment
      openSegments.erase(std::find(std::begin(openSegments), std::end(openSegments), segment));
    }
    /*
     * Third case: An intersection.
     */
    else { // event.type == "intersection"
      intersections.push_back(event.point);

      auto it1 = std::find(std::begin(openSegments), std::end(openSegments), event.s1);
      auto it2 = std::find(std::begin(openSegments), std::end(openSegments), event.s2);
      std::iter_swap(it1, it2);

      if(hasPrevious(openSegments, event.s2)) {
        Segment prev = getPrevious(openSegments, event.s2);

        Point intersection = intersect(event.s2, prev);
        if(!isinf(intersection.x) && intersection.x > lineX) {
          events.insert({"intersection", intersection, prev, event.s2});
        }
      }

      if(hasNext(openSegments, event.s1)) {
        Segment next = getNext(openSegments, event.s1);

        Point intersection = intersect(next, event.s1);
        if(!isinf(intersection.x) && intersection.x > lineX) {
          events.insert({"intersection", intersection, event.s1, next});
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

      Point intersection = intersect(*it1, *it2);
      if(!isinf(intersection.x)) {
        intersections.push_back(intersection);
      }
    }
  }

  return intersections;
}

#endif
