#ifndef BUW_LINE_HPP
#define BUW_LINE_HPP

#include <ostream>
#include "point.hpp"

struct Line
{
  Point a;
  Point b;
};

std::ostream& operator<<(std::ostream& os, Line const& line)
{
  os << line.a << " -- " << line.b;
  return os;
}

bool operator==(Line const& lhs, Line const& rhs)
{
  return lhs.a == rhs.a && lhs.b == rhs.b;
}

#endif