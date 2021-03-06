#include <eve/function/extract.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};
  wide_it pi = {-1, 2, -3, -32768};

  std::cout << "---- simd" << '\n'
            << "<- pf =                            " << pf << '\n'
            << "-> eve::extract(pf, 2) =           " << eve::extract(pf, 2) << '\n'
            << "<- pi =                            " << pi << '\n'
            << "-> eve::extract(pi, 0) =           " << eve::extract(pi, 0) << '\n';

  float        xf = -32768.0f;
  std::int16_t xi = -32768;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                            " << xf << '\n'
            << "-> eve::extract(xf, 0) =           " << eve::extract(xf, 0) << '\n'
            << "<- xi =                            " << xi << '\n'
            << "-> eve::extract(xi, 0) =           " << eve::extract(xi, 0) << '\n';
  return 0;
}
