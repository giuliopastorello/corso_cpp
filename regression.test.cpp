#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "point.hpp"
#include "regression.hpp"

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
