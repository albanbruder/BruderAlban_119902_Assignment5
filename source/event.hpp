#ifndef BUW_EVENT_HPP
#define BUW_EVENT_HPP

#include <string>
#include "point.hpp"
#include "segment.hpp"

struct Event
{
  std::string type;
  Point point;
  Segment s1;
  Segment s2;
};

std::ostream& operator<<(std::ostream& os, Event const& e)
{
  os << e.type << " " << e.point;
  return os;
}

bool operator==(Event const& lhs, Event const& rhs)
{
  return lhs.type == rhs.type && lhs.point == rhs.point;
}

#endif