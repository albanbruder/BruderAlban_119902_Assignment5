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

/**
 * The Bentley-Ottmann algorithm for finding 
 * the intersections in a set.
 */
std::vector<Point> bentleyOttmannIntersections(std::vector<Segment> const& segments)
{
  // get all the point
  Set<Event> events;
  for(Segment const& segment : segments) {
    // ensure that correct event type is used
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

  // as long as there are unhandled points or intersections
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

      // get an iterator pointing at the segment in openSegments
      auto it = std::find(std::cbegin(openSegments), std::cend(openSegments), segment);

      // if there is a previous segment
      // intersect with previous neighbor
      if(it != std::cbegin(openSegments)) {
        auto prev = std::prev(it);

        Point intersection = intersect(*it, *prev);

        // if there is a intersection -> insert into events
        if(!isinf(intersection.x)) {
          events.insert({"intersection", intersection, *prev, *it});
        }
      }

      // if there is a next segment
      // intersect with next neighbor
      if(std::next(it) != std::cend(openSegments)) {
        auto next = std::next(it);

        Point intersection = intersect(*it, *next);

        // if there is a intersection -> insert into events
        if(!isinf(intersection.x)) {
          events.insert({"intersection", intersection, *it, *next});
        }
      }

    }


    /*
     * Second case: A segment ends.
     */
    else if(event.type == "close") {
      // get an iterator pointing at the current segment
      auto it = std::find(std::cbegin(openSegments), std::cend(openSegments), segment);

      // if there is a previous and a next segment
      // intersect previous and next neighbor
      if(it != std::cbegin(openSegments) && std::next(it) != std::cend(openSegments)) {
        auto prev = std::prev(it);
        auto next = std::next(it);

        Point intersection = intersect(*prev, *next);

        // if there is a intersection -> insert into events
        if(!isinf(intersection.x) && intersection.x >= lineX) {
          events.insert({"intersection", intersection, *prev, *next});
        }
      }

      // remove segment from openSegments
      openSegments.erase(it);
    }


    /*
     * Third case: An intersection.
     */
    else { // event.type == "intersection"
      // add intersection point to output list
      intersections.push_back(event.point);

      // get iterators for the intersecting segments
      auto it1 = std::find(std::begin(openSegments), std::end(openSegments), event.s1);
      auto it2 = std::find(std::begin(openSegments), std::end(openSegments), event.s2);

      // swap intersecting segments
      std::iter_swap(it1, it2);

      // if segment_2 has a previous neighbor
      if(it1 != std::begin(openSegments)) {
        auto prev = std::prev(it1);

        Point intersection = intersect(*it1, *prev);

        // if there is a intersection -> insert into events
        if(!isinf(intersection.x) && intersection.x > lineX) {
          events.insert({"intersection", intersection, *prev, *it1});
        }
      }

      // if segment_1 has a next neighbor
      if(std::next(it2) != std::end(openSegments)) {
        auto next = std::next(it2);

        Point intersection = intersect(*next, *it2);

        // if there is a intersection -> insert into events
        if(!isinf(intersection.x) && intersection.x > lineX) {
          events.insert({"intersection", intersection, *it2, *next});
        }
      }
    }
  }

  return intersections;
}


/**
 * Returns all intersections between the given segments.
 * Uses brute force.
 */
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
