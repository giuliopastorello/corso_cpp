#ifndef POINT_HPP
#define POINT_HPP


struct Point
{
  double x;
  double y;
};

bool operator==(Point const& left, Point const& right) noexcept;

bool operator!=(Point const& left, Point const& right) noexcept;

#endif