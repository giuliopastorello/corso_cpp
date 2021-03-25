#ifndef REGRESSION_HPP
#define REGRESSION_HPP

#include <algorithm>
#include <stdexcept>
#include <vector>
#include "point.hpp"

class Point;

class Regression
{
 public:
  struct Result
  {
    double A;
    double B;
  };

 private:
  std::vector<Point> points{};

 public:
  void add(Point const&);

  void add(double x, double y);
  
  bool remove(Point const& p) noexcept;
  
  bool remove(double x, double y) noexcept;
  
  Result fit() const;
  
  int size() const noexcept;
  
  int empty() const noexcept;
  
};

Regression::Result fit(Regression const& reg);

#endif