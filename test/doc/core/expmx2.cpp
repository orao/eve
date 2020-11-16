#include <eve/function/expmx2.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  using eve::pedantic;

wide_ft pf = {0.0f, -0.0f, -1.0f, 1.0f, 2.0f,
               eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf         = " << pf << '\n'
            << "-> expmx2(pf) = " << eve::expmx2(pf) << '\n';

  float xf = 3.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf         = " << xf << '\n'
            << "-> expmx2(xf) = " << eve::expmx2(xf) << '\n';
  return 0;
}
