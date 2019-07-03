#ifndef BUW_LINE_HPP
#define BUW_LINE_HPP

#include <ostream>
#include "point.hpp"

/**
 * Representation of a streight line.
 */
struct Line
{
  Point a;
  Point b;
};

/**
 * Print line to stream output.
 */
std::ostream& operator<<(std::ostream& os, Line const& line)
{
  os << line.a << " -- " << line.b;
  return os;
}

/**
 * Compare 2 lines by there points.
 */
bool operator==(Line const& lhs, Line const& rhs)
{
  return lhs.a == rhs.a && lhs.b == rhs.b;
}

#endif