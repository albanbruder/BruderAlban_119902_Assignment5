#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <math.h>

#include "line.hpp"
#include "segment.hpp"

/**
 * Checks if a point p is in the bounding box spanned by points a and b.
 */
bool between(Point const& p, Point const& a, Point const& b) {
  // check for x-coordinates
  if(p.x < std::min(a.x, b.x) || p.x > std::max(a.x, b.x)) {
    return false;
  }

  // check for y-coordinates
  if(p.y < std::min(a.y, b.y) || p.y > std::max(a.y, b.y)) {
    return false;
  }

  return true;
}

/**
 * Intersects 2 lines. (not segments)
 * Returns the point of intersection or a point with x and y set to infinity.
 */
Point intersect(Line const& line1, Line const& line2) {
  // a1*x + b1*y = c1
  float a1 = line1.b.y - line1.a.y;
  float b1 = line1.a.x - line1.b.x;
  float c1 = a1*line1.a.x + b1*line1.a.y;

  // a2*x + b2*y = c2
  float a2 = line2.b.y - line2.a.y;
  float b2 = line2.a.x - line2.b.x;
  float c2 = a2*line2.a.x + b2*line2.a.y;

  float det = a1*b2 - a2*b1;

  // lines are parallel
  if(det == 0) {
    return Point();
  }

  float x = (b2*c1 - b1*c2) / det;
  float y = (a1*c2 - a2*c1) / det;
  return Point{ x, y };
}

/**
 * Intersects a line and a segment.
 * Returns the point of intersection or a point with x and y set to infinity.
 */
Point intersect(Line const& line, Segment const& segment) {
  Point intersection = intersect(line, Line{ segment.a, segment.b });

  if(!between(intersection, segment.a, segment.b)) {
    return Point();
  } else {
    return intersection;
  }
}

/**
 * Intersect 2 segments.
 */
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

/**
 * Generate a random Point.
 */
Point generateRandomPoint(int minX, int maxX, int minY, int maxY)
{
  float x = minX + std::rand() % (( maxX + 1 ) - minX);
  float y = minY + std::rand() % (( maxY + 1 ) - minY);
  return Point{x, y};
}

/**
 * Generate a random vector of segments.
 */
std::vector<Segment> generateRandomSegements(unsigned int n, int minX, int maxX, int minY, int maxY)
{
  // initialize the randomizer
  srand(time(0));
  
  std::vector<Point> points;
  std::vector<Segment> segments;

  // as long as the list is not full
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
      return a.x == p.x || b.x == p.x;
    });
    if(it != std::cend(points)) {
      continue;
    }

    /* std::vector<Point> intersections;
    bool duplicateFound = false;
    for(auto seg : segments) {
      Point intersection = intersect(seg, Segment{a, b});
      if(isinf(intersection.x)) {
        continue;
      }

      auto it = std::find_if(std::cbegin(intersections), std::cend(intersections), [intersection](Point const& p) {
        return p.x == intersection.x;
      });
      if(it != std::cend(intersections)) {
        duplicateFound = true;
      } else {
        intersections.push_back(intersection);
      }
    }

    if(duplicateFound) {
      continue;
    }

    points.push_back(a);
    points.push_back(b);

    for(auto p : intersections) {
      points.push_back(p);
    } */

    segments.push_back({ a, b });
  }

  return segments;
}