#include "algorithm.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
  unsigned int n = 10;
  int minX = 0;
  int maxX = 10;
  int minY = 0;
  int maxY = 10;

  auto segments = generateRandomSegements(n, minX, maxX, minY, maxY);

  std::cout << "<<< GENERATED SEGMENTS >>>" << std::endl;
  for(auto segment : segments) {
    std::cout << segment << std::endl;
  }
  std::cout << std::endl;

  auto boIntersections = bentleyOttmannIntersections(segments);
  auto bfIntersections = bruteForceIntersections(segments);

  /*
   * Print all intersections
   */
  std::cout << "<<< INTERSECTIONS USING BENTLEY-OTTMANN >>>" << std::endl;
  for(auto i : boIntersections) {
    std::cout << i << std::endl;
  }
  std::cout << std::endl;

  std::cout << "<<< INTERSECTIONS USING BRUTE FORCE >>>" << std::endl;
  for(auto i : bfIntersections) {
    std::cout << i << std::endl;
  }
  std::cout << std::endl;

  // check if Bentley-Ottmann algorithm found all points
  bool foundAll = true;
  for(auto i : bfIntersections) {
    auto it = std::find(std::cbegin(boIntersections), std::cend(boIntersections), i);
    if(it == std::cend(boIntersections)) {
      foundAll = false;
      break;
    }
  }

  std::cout << "Result is " << (foundAll ? "CORRECT" : "INCORRECT") << "!" << std::endl;
}
