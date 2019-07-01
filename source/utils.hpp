#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#include "segment.hpp"

Point generateRandomPoint(int minX, int maxX, int minY, int maxY)
{
  int x = minX + std::rand() % (( maxX + 1 ) - minX);
  int y = minY + std::rand() % (( maxY + 1 ) - minY);
  return Point{x, y};
}

std::vector<Segment> generateRandomSegements(unsigned int n, int minX, int maxX, int minY, int maxY)
{
  srand(time(0));
  
  std::vector<Point> points;
  std::vector<Segment> segments;
  while(segments.size() < n) {
    Point a = generateRandomPoint(minX, maxX, minY, maxY);
    Point b = generateRandomPoint(minX, maxX, minY, maxY);
    
    // check if line is vertical
    // or inverse
    if(a.x >= b.x) {
      continue;
    }

    // check if one of the points already exists
    auto it = std::find_if(std::cbegin(points), std::cend(points), [a, b](Point const& p) {
      return (a.x == p.x && a.y == p.y) || (b.x == p.x && b.y == p.y);
    });
    if(it != std::cend(points)) {
      continue;
    }

    points.push_back(a);
    points.push_back(b);
    segments.push_back({ a, b });
  }

  return segments;
}

Segment findSegment(std::vector<Segment> const& segments, Point const& p) {
  auto it = std::find_if(
      std::cbegin(segments), 
      std::cend(segments), 
      [&p](Segment const& s) { return (s.a == p || s.b == p); }
    );
  return *it;
}

bool between(Point const& p, Point const& a, Point const& b) {
  if(p.x < std::min(a.x, b.x) || p.x > std::max(a.x, b.x)) {
    return false;
  }
  if(p.y < std::min(a.y, b.y) || p.y > std::max(a.y, b.y)) {
    return false;
  }

  return true;
}

std::pair<bool, Point> intersectLine(Segment const& s1, Segment const& s2) {
  Point p0{0,0};

  float a1 = s1.b.y - s1.a.y;
  float b1 = s1.a.x - s1.b.x;
  float c1 = a1*s1.a.x + b1*s1.a.y;

  float a2 = s2.b.y - s2.a.y;
  float b2 = s2.a.x - s2.b.x;
  float c2 = a2*s2.a.x + b2*s2.a.y;

  float det = a1*b2 - a2*b1;
  if(det == 0) {
    // segments are parallel
    return std::make_pair(false, p0);
  }

  float x = (b2*c1 - b1*c2) / det;
  float y = (a1*c2 - a2*c1) / det;
  Point p{ x, y };
  return std::make_pair(true, p);
}

std::pair<bool, Point> intersectSegment(Segment const& s1, Segment const& s2)
{
  Point p0{0,0};
  auto result = intersectLine(s1, s2);
  if(!result.first) {
    return result;
  }

  Point p = result.second;

  // check for both segments if Point(x,y) is between Point a and b
  if(between(p, s1.a, s1.b) && between(p, s2.a, s2.b)) {
    return std::make_pair(true, p);
  } else {
    return std::make_pair(false, p0);
  }
}
