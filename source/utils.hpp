#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#include "line.hpp"
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

Point intersect(Line const& line1, Line const& line2) {
  float a1 = line1.b.y - line1.a.y;
  float b1 = line1.a.x - line1.b.x;
  float c1 = a1*line1.a.x + b1*line1.a.y;

  float a2 = line2.b.y - line2.a.y;
  float b2 = line2.a.x - line2.b.x;
  float c2 = a2*line2.a.x + b2*line2.a.y;

  float det = a1*b2 - a2*b1;
  if(det == 0) {
    // lines are parallel
    return Point();
  }

  float x = (b2*c1 - b1*c2) / det;
  float y = (a1*c2 - a2*c1) / det;
  return Point{ x, y };
}

Point intersect(Line const& line, Segment const& segment) {
  Point intersection = intersect(line, Line{ segment.a, segment.b });

  if(!between(intersection, segment.a, segment.b)) {
    return Point();
  } else {
    return intersection;
  }
}

Point intersect(Segment const& segment1, Segment const& segment2)
{
  Point intersection = intersect(Line{ segment1.a, segment1.b }, segment2);

  // check for both segments if Point(x,y) is between Point a and b
  if(!between(intersection, segment1.a, segment1.b)) {
    return Point();
  } else {
    return intersection;
  }
}


template <typename Container, typename T>
bool hasPrevious(Container const& c, T const& v)
{
  auto it = std::find(std::cbegin(c), std::cend(c), v) - 1;
  return (it != (std::cbegin(c) - 1));
}

template <typename Container, typename T>
T getPrevious(Container const& c, T const& v)
{
  auto it = std::find(std::cbegin(c), std::cend(c), v) - 1;
  return *it;
}

template <typename Container, typename T>
bool hasNext(Container const& c, T const& v)
{
  auto it = std::find(std::cbegin(c), std::cend(c), v) + 1;
  return (it != std::cend(c));
}

template <typename Container, typename T>
T getNext(Container const& c, T const& v)
{
  auto it = std::find(std::cbegin(c), std::cend(c), v) + 1;
  return *it;
}