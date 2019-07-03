#include "algorithm.hpp"

#include "cxxopts.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
  /**
   * Use the cxxopts commandline argument parser.
   */
  cxxopts::Options options(argv[0], "Bentley–Ottmann algorithm");
  options
    .positional_help("[optional args]")
    .show_positional_help();

  options.add_options()
    ("h,help", "give this help list")
    ("n,num", "number of segments to generate", cxxopts::value<unsigned int>()->default_value("10"))
    ("x,minX", "minimum x value", cxxopts::value<float>()->default_value("-100"))
    ("X,maxX", "maximum x value", cxxopts::value<float>()->default_value("100"))
    ("y,minY", "minimum y value", cxxopts::value<float>()->default_value("-100"))
    ("Y,maxY", "maximum y value", cxxopts::value<float>()->default_value("100"));

  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    std::cout << options.help({"", "Group"}) << std::endl;
    exit(0);
  }

  unsigned int n = result["num"].as<unsigned int>();
  float minX = result["minX"].as<float>();
  float maxX = result["maxX"].as<float>();
  float minY = result["minY"].as<float>();
  float maxY = result["maxY"].as<float>();

  // generate random segments
  auto segments = generateRandomSegements(n, minX, maxX, minY, maxY);

  // print all segments
  std::cout << "<<< GENERATED SEGMENTS >>>" << std::endl;
  for(auto segment : segments) {
    std::cout << segment << std::endl;
  }
  std::cout << std::endl;

  // run both algorithms on the generated segments
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
