#ifndef BUW_POINT_HPP
#define BUW_POINT_HPP

#include <ostream>

struct Point
{
  float x;
  float y;
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