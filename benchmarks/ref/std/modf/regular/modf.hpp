//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>
#include <tuple>

int main(int argc, char** argv)
{
  auto lmin = eve::valmin(eve::as<EVE_TYPE>());
  auto lmax = eve::valmax(eve::as<EVE_TYPE>());
  auto std_modf =  [](auto x){ EVE_TYPE y;  auto z = std::modf(x, &y); return std::make_tuple(z, y); };
  EVE_REGISTER_BENCHMARK(std_modf, EVE_TYPE
    , eve::bench::random<EVE_TYPE>(lmin,lmax));

  eve::bench::start_benchmarks(argc, argv);
}
