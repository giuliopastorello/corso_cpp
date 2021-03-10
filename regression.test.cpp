#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

struct Result
{
  double A;
  double B;
};

class Regression
{
  int N{};
  double sum_x{};
  double sum_y{};
  double sum_x2{};
  double sum_xy{};
 public:
  void add(double x, double y)
  {
    ++N;
    sum_x += x;
    sum_y += y;
    sum_x2 += x * x;
    sum_xy += x * y;
  }
  Result fit() const
  {
    double const a = (sum_y * sum_x2 - sum_x * sum_xy) / (N * sum_x2 - sum_x * sum_x);
    double const b = (N * sum_xy - sum_x * sum_y) / (N * sum_x2 - sum_x * sum_x);
    return {a, b};
  }
};

TEST_CASE("Testing Regression") {
  Regression reg;
  reg.add(0., 0.);
  reg.add(1., 1.);
  reg.add(3., 3.);
  reg.add(4., 4.);
  auto result = reg.fit();
  CHECK(result.A == doctest::Approx(0.));
  CHECK(result.B == doctest::Approx(1.)); 
}

TEST_CASE("Testing Regression") {
  Regression reg;
  reg.add(0., 0.);
  reg.add(1., 2.);
  reg.add(3., 6.);
  reg.add(4., 8.);
  auto result = reg.fit();
  CHECK(result.A == doctest::Approx(0.));
  CHECK(result.B == doctest::Approx(2.)); 
}

TEST_CASE("Testing Regression") {
  Regression reg;
  reg.add(1., 4.319486);
  reg.add(2., 4.268998);
  reg.add(3., 4.217299);
  reg.add(4., 4.16589);
  reg.add(5., 4.121473);
  reg.add(6., 4.081766);
  reg.add(7., 4.031482);
  reg.add(8., 3.997283);
  reg.add(9., 3.965564);
  reg.add(10., 3.920983);
  reg.add(11., 3.874321);
  reg.add(12., 3.816613);
  reg.add(13., 3.80999);
  reg.add(14., 3.778492);
  reg.add(15., 3.741235);
  reg.add(16., 3.68261);
  reg.add(17., 3.677566);
  reg.add(18., 3.612268);
  reg.add(19., 3.598681);
  reg.add(20., 3.57655);
  reg.add(21., 3.52783);
  reg.add(22., 3.51898);
  reg.add(23., 3.491952);
  reg.add(24., 3.451574);
  reg.add(25.,3.435599);
  reg.add(26.,3.409496);
  reg.add(27.,3.389462);
  reg.add(28.,3.36557);
  auto result = reg.fit();
  CHECK(result.A == doctest::Approx(4.28959299));
  CHECK(result.B == doctest::Approx(-0.035121899)); 
}
