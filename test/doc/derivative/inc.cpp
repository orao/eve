#include <eve/function/derivative/inc.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -2.0f, 10.0f, 200.0f, -1000.0f,
               eve::inf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                                = " << pf << '\n'
            << "-> eve::derivative(eve::inc)(pf)     = " << eve::derivative(eve::inc)(pf) << '\n'
            << "-> eve::derivative(eve::inc)(pf, 2u) = " << eve::derivative(eve::inc)(pf, 2u) << '\n'
            << "-> eve::derivative(eve::inc)(pf, 3u) = " << eve::derivative(eve::inc)(pf, 3u) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                            = " << xf << '\n'
            << "-> eve::derivative(eve::inc)(xf) = " << eve::derivative(eve::inc)(xf) << '\n';
  return 0;
}