#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

struct Result
{
  double A;
  double B;
};

class Regression
{
  int N_{};
  double sum_x_{};
  double sum_y_{};
  double sum_xy_{};
  double sum_x2_{};

 public:
  void add(double x, double y)
  {
    ++N_;
    sum_x_ += x;
    sum_y_ += y;
    sum_xy_ += x * y;
    sum_x2_ += x * x;
  }
  Result fit() const
  {
    // assert(N_ >= 2); // un po' brutale
    if (N_ < 2) {
      throw std::runtime_error{"not enough points"};
    }
    double const d = (N_ * sum_x2_ - sum_x_ * sum_x_);
    if (d == 0.) {
      throw std::runtime_error{"vertical line"};
    }
    double const a = (sum_y_ * sum_x2_ - sum_x_ * sum_xy_) / d;
    double const b = (N_ * sum_xy_ - sum_x_ * sum_y_) / d;
    return {a, b};
  }
  int size() const
  {
    return N_;
  }
};

auto fit(Regression const& reg)
{
  // the following call would fail compilation if the fit method weren't const
  return reg.fit();
}

TEST_CASE("testing Regression")
{
  Regression reg;

  REQUIRE(reg.size() == 0);

  SUBCASE("fitting with no points throws")
  {
    CHECK_THROWS(reg.fit());
  }

  SUBCASE("fitting on one point throws")
  {
    reg.add(0., 0.);
    CHECK_THROWS(reg.fit());
  }

  SUBCASE("fitting on two points")
  {
    reg.add(0., 0.);
    reg.add(1., 1.);
    auto result = reg.fit();
    CHECK(result.A == doctest::Approx(0));
    CHECK(result.B == doctest::Approx(1));
  }

  SUBCASE("fitting on two points, negative slope")
  {
    reg.add(0., 1.);
    reg.add(1., 0.);
    auto result = reg.fit();
    CHECK(result.A == doctest::Approx(1));
    CHECK(result.B == doctest::Approx(-1));
  }

  SUBCASE("fitting on two points aligned vertically throws")
  {
    reg.add(1., 0.);
    reg.add(1., 2.);
    CHECK_THROWS(reg.fit());
  }

  SUBCASE("fitting on five points")
  {
    reg.add(2.1, 3.2);
    reg.add(6.9, 7.3);
    reg.add(2.2, 3.0);
    reg.add(0.1, 1.3);
    reg.add(4.7, 5.6);
    auto result = reg.fit();
    CHECK(result.A == doctest::Approx(1.2).epsilon(0.01));
    CHECK(result.B == doctest::Approx(0.9).epsilon(0.01));
  }

  SUBCASE("a case from a student, using free function")
  {
    reg.add(1, 1);
    reg.add(3, 5);
    reg.add(3.7, 10.2);
    reg.add(4.2, 11.8);
    auto result = fit(reg);
    CHECK(result.A == doctest::Approx(-3.04).epsilon(0.01));
    CHECK(result.B == doctest::Approx(3.37).epsilon(0.01));
  }
}
