#include "point.hpp"
#include "regression.hpp"

#include <iostream>

int main()
{
  try {
    Regression reg;

    char c;
    double a, b;
    while (std::cin >> c >> a >> b) {
      switch (c) {
        case 'a':
          reg.add(a, b);
          break;
        case 'r':
          if (!reg.remove(a, b)) {
            std::cerr << "Point non present (" << a << ',' << b << ")\n";
          }
          break;
        default:
          std::cerr << "Invalid command '" << c << "'\n";
          break;
      }
    }

    auto result = reg.fit();

    std::cout << "The regression line is Y = " << result.A << " + " << result.B
              << " * X\n";

  } catch (std::exception const& e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "Caught unknown exception\n";
    return EXIT_FAILURE;
  }
}
