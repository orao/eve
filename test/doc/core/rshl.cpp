#include <eve/function/rshl.hpp>
#include <eve/wide.hpp>
#include <iostream>

using iT      = std::int32_t;
using wide_it = eve::wide<iT, eve::fixed<4>>;

int main()
{
  wide_it pi = {100, 200, -2, 3};
  wide_it qi = {1, -2, 3, -1};

  std::cout << "---- simd" << '\n'
            << "<- pi            = " << pi << '\n'
            << "<- qi            = " << qi << '\n'
            << "-> shl(pi, qi)   = " << eve::rshl(pi, qi) << '\n';

  iT xi = 2, mxi = -2, yi = 3;

  std::cout << "---- scalar" << '\n'
            << "<- xi            = " << xi << '\n'
            << "<- mxi           = " << mxi << '\n'
            << "<- yi            = " << yi << '\n'
            << "-> rshl(xi, yi)  = " << eve::rshl(xi, yi) << '\n'
            << "-> rshl(mxi, yi) = " << eve::rshl(mxi, yi) << '\n';
  return 0;
}
