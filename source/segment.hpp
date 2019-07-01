#ifndef BUW_SEGMENT_HPP
#define BUW_SEGMENT_HPP

#include <ostream>
#include "point.hpp"

struct Segment
{
  Point a;
  Point b;
};

std::ostream& operator<<(std::ostream& os, Segment const& s)
{
  os << s.a << " -- " << s.b;
  return os;
}

bool operator==(Segment const& lhs, Segment const& rhs)
{
  return lhs.a == rhs.a && lhs.b == rhs.b;
}

#endif