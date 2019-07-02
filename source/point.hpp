#ifndef BUW_POINT_HPP
#define BUW_POINT_HPP

#include <ostream>
#include <limits>

struct Point
{
  float x = std::numeric_limits<float>::infinity();
  float y = std::numeric_limits<float>::infinity();
};

std::ostream& operator<<(std::ostream& os, Point const& p)
{
  os << "(x: " << p.x << ", y: " << p.y << ")";
  return os;
}

bool operator==(Point const& lhs, Point const& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}


#endif