#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <stdexcept>
#include <vector>

struct Point
{
  double x;
  double y;
};

bool operator==(Point const& left, Point const& right) noexcept
{
  return left.x == right.x && left.y == right.y;
}

bool operator!=(Point const& left, Point const& right) noexcept
{
  return !(left == right);
}

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
  void add(Point const& p)
  {
    points.push_back(p);
  }
  void add(double x, double y)
  {
    return add({x, y});
  }
  bool remove(Point const& p) noexcept
  {
    auto const it = std::find(points.begin(), points.end(), p);
    if (it != points.end()) {
      points.erase(it);
      return true;
    } else {
      return false;
    }
  }
  bool remove(double x, double y) noexcept
  {
    return remove({x, y});
  }
  Result fit() const
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
  int size() const noexcept
  {
    return points.size();
  }
  int empty() const noexcept
  {
    return size() == 0;
  }
};

auto fit(Regression const& reg)
{
  return reg.fit();
}

TEST_CASE("testing Regression")
{
  {
    Regression reg;

    REQUIRE(reg.empty());

    CHECK_THROWS(reg.fit());

    reg.add(0., 0.);
    CHECK_THROWS(reg.fit());

    reg.add(1., 1.);
    Regression::Result result = reg.fit();
    CHECK(result.A == doctest::Approx(0));
    CHECK(result.B == doctest::Approx(1));
  }

  {
    Regression reg;
    reg.add(0., 1.);
    reg.add(1., 0.);
    auto result = reg.fit();
    CHECK(result.A == doctest::Approx(1));
    CHECK(result.B == doctest::Approx(-1));
  }

  {
    Regression reg;

    reg.add(1., 0.);
    reg.add(1., 2.);
    CHECK_THROWS(reg.fit());
  }

  {
    Regression reg;
    reg.add(2.1, 3.2);
    reg.add(6.9, 7.3);
    reg.add(2.2, 3.0);
    reg.add(0.1, 1.3);
    reg.add(4.7, 5.6);
    auto result = reg.fit();
    CHECK(result.A == doctest::Approx(1.2).epsilon(0.01));
    CHECK(result.B == doctest::Approx(0.9).epsilon(0.01));
  }

  {
    Regression reg;
    reg.add(1, 1);
    reg.add(3, 5);
    reg.add(3.7, 10.2);
    reg.add(4.2, 11.8);
    auto result = fit(reg);
    CHECK(result.A == doctest::Approx(-3.04).epsilon(0.01));
    CHECK(result.B == doctest::Approx(3.37).epsilon(0.01));
  }

  {
    Regression reg;
    CHECK(reg.remove(0., 0.) == false);
    CHECK(reg.empty());
  }

  {
    Regression reg;
    reg.add(0., 0.);
    reg.add(1., 1.);
    CHECK(reg.remove(0., 0.) == true);
    CHECK(reg.size() == 1);
  }

  {
    Regression reg;
    reg.add(0., 0.);
    reg.add(1., 1.);
    CHECK(reg.remove(1., 0.) == false);
    CHECK(reg.size() == 2);
  }

  {
    Regression reg;
    reg.add(0., 0.);
    reg.add(1., 1.);
    CHECK(reg.remove(0., 0.) == true);
    CHECK(reg.remove(0., 0.) == false);
    CHECK(reg.size() == 1);
  }

  {
    Regression reg;
    reg.add(0., 0.);
    reg.add(1., 1.);
    reg.add(.5, 3.);
    CHECK(reg.remove(0.5, 3.) == true);
    CHECK(reg.size() == 2);
    auto result = reg.fit();
    CHECK(result.A == doctest::Approx(0));
    CHECK(result.B == doctest::Approx(1));
  }

  {
    Regression reg;
    reg.add(0., 0.);
    reg.add({1., 1.});
    reg.add(Point{.5, 3.});
    CHECK(reg.remove({0.5, 3.}) == true);
    CHECK(reg.size() == 2);
    auto result = reg.fit();
    CHECK(result.A == doctest::Approx(0));
    CHECK(result.B == doctest::Approx(1));
  }
}
