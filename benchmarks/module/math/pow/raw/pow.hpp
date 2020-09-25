//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pow.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-1.0);
  auto lmax = EVE_VALUE(100.0);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__pow = [](auto x, auto y){return std::pow(x, y);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__pow) , xp, std__pow , arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(raw_(eve::pow)) , xp, eve::raw_(eve::pow) , arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(raw_(eve::pow)) , xp, eve::raw_(eve::pow) , arg0, arg1);

}