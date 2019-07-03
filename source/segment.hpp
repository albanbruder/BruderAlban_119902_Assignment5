#ifndef BUW_SEGMENT_HPP
#define BUW_SEGMENT_HPP

#include <ostream>
#include "point.hpp"

/**
 * Representation of a segment. Constrained by points a and b.
 */
struct Segment
{
  Point a;
  Point b;
};

/**
 * Print segment to output stream.
 */
std::ostream& operator<<(std::ostream& os, Segment const& s)
{
  os << s.a << " -- " << s.b;
  return os;
}

/**
 * Compare 2 segments by there points.
 */
bool operator==(Segment const& lhs, Segment const& rhs)
{
  return lhs.a == rhs.a && lhs.b == rhs.b;
}

#endif