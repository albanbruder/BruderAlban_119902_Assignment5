#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include <vector>
#include "mergesort.hpp"

TEST_CASE("mergsort worst case", "[mergesort]")
{
  std::vector<int> vector{9,8,7,6,5,4,3,2,1,0};
  buw::mergesort(std::begin(vector), std::end(vector), std::less<int>());
  REQUIRE(std::is_sorted(std::cbegin(vector), std::cend(vector)));
}

TEST_CASE("mergesort", "[mergesort]")
{
  std::vector<int> vector{-5, 10, 0, 1, 4, 0, -6};
  buw::mergesort(std::begin(vector), std::end(vector), std::less<int>());
  REQUIRE(std::is_sorted(std::cbegin(vector), std::cend(vector)));
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
