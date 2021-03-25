#include "point.hpp"

bool operator==(Point const& left, Point const& right) noexcept
{
  return left.x == right.x && left.y == right.y;
}

bool operator!=(Point const& left, Point const& right) noexcept
{
  return !(left == right);
}