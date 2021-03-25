#include "regression.hpp"
#include "point.hpp"

#include <algorithm>
#include <stdexcept>

void Regression::add(Point const& p)
{
  points.push_back(p);
}

void Regression::add(double x, double y)
{
  return add({x, y});
}
bool Regression::remove(Point const& p) noexcept
{
  auto const it = std::find(points.begin(), points.end(), p);
  if (it != points.end()) {
    points.erase(it);
    return true;
  } else {
    return false;
  }
}
bool Regression::remove(double x, double y) noexcept
{
  return remove({x, y});
}
Regression::Result Regression::fit() const
{
  int const N = points.size();
  if (N < 2) {
    throw std::runtime_error{"not enough points"};
  }

  double sum_x{};
  double sum_y{};
  double sum_xy{};
  double sum_x2{};

  for (auto const& p : points) {
    sum_x += p.x;
    sum_y += p.y;
    sum_xy += p.x * p.y;
    sum_x2 += p.x * p.x;
  }

  double const d = (N * sum_x2 - sum_x * sum_x);
  if (d == 0.) {
    throw std::runtime_error{"vertical line"};
  }
  double const a = (sum_y * sum_x2 - sum_x * sum_xy) / d;
  double const b = (N * sum_xy - sum_x * sum_y) / d;
  return {a, b};
}
int Regression::size() const noexcept
{
  return points.size();
}
int Regression::empty() const noexcept
{
  return size() == 0;
}
Regression::Result fit(Regression const& reg)
{
  return reg.fit();
}
