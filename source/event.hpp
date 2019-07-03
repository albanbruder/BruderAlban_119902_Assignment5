#ifndef BUW_EVENT_HPP
#define BUW_EVENT_HPP

#include <string>
#include "point.hpp"
#include "segment.hpp"

/**
 * Represents a start, end or intersection point.
 */
struct Event
{
  // the type of point (start | end | intersection)
  std::string type;

  // the point itself
  Point point;

  // segment corresponding to the point
  Segment s1;

  // second segment (only used if it is an intersection)
  Segment s2;
};

/**
 * Print to stream output.
 */
std::ostream& operator<<(std::ostream& os, Event const& e)
{
  os << e.type << " " << e.point;
  return os;
}

/**
 * Compare 2 events by there type and point.
 */
bool operator==(Event const& lhs, Event const& rhs)
{
  return lhs.type == rhs.type && lhs.point == rhs.point;
}

/**
 * Compare 2 events by there x-coordinate.
 */
bool operator<(Event const& lhs, Event const& rhs)
{
  return lhs.point.x < rhs.point.x;
}

#endif