//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/expx2m.hpp>
#include <eve/function/exp.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/concept/value.hpp>
#include <eve/platform.hpp>

#include <eve/concept/value.hpp>
#include <cmath>


#include <eve/function/average.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/next.hpp>

template <typename T,typename F> void detect_max(F func)
{
  using v_t =  eve::element_type_t<T>;
  auto vmin = eve::range_max<T>(func)*v_t(0.1);
  auto vmax = eve::range_max<T>(func)*v_t(10);
  std::cout << vmin << " <= " << vmax << std::endl;
  std::cout << func(vmin)<< std::endl;
  std::cout << func(vmax)<< std::endl;
//  if (vmin <  vmax) std::swap(vmin, vmax);
  if(func(vmin) > 0 && func(vmax) == 0)
  {
    while(true)
    {
      auto v =  eve::average(vmax, vmin);
      if (func(v) > 0) vmin = v;  else vmax = v;
//         std::cout << "vmax " << vmax <<  std::endl;
//         std::cout << "vmin " << vmin <<  std::endl;
//         std::cout << "vmin > vmax   " << (vmin > vmax) <<  std::endl;
      if(vmax <=  eve::next(vmin))
      {
        std::cout << "n " << std::hexfloat << eve::next(v) << " -> " << func(eve::next(v)) << " -> " << std::defaultfloat << std::setprecision(16) << eve::next(v) << std::endl;
        std::cout << "v " << std::hexfloat << v << " -> " << func(v) <<                       " -> " << std::defaultfloat << std::setprecision(16) << v << std::endl;
        std::cout << "p " << std::hexfloat << eve::prev(v) << " -> " << func(eve::prev(v)) << " -> " << std::defaultfloat << std::setprecision(16) << eve::prev(v) << std::endl;
        break;
      }
    }
  }
  else
    std::cout << "zut" << std::endl;
}


TTS_CASE_TPL("Check eve::expx2m properties", EVE_TYPE)
{
  auto reg = eve::expx2m;
  using v_t = eve::element_type_t<T>;
  detect_max<T>(reg);
  TTS_ULP_EQUAL (reg(eve::prev(eve::range_min<T>(reg))), eve::zero(eve::as<v_t>()), 0.5);
  TTS_EXPECT(reg(eve::range_min<T>(reg)) >  0 );
  TTS_ULP_EQUAL (reg(eve::next(eve::range_max<T>(reg))), eve::zero(eve::as<v_t>()), 0.5);
  TTS_EXPECT(reg(eve::range_max<T>(reg)) > 0);
}

TTS_CASE_TPL("Check eve::expx2m return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::expx2m(T()), T);
}

TTS_CASE_TPL("Check eve::expx2m behavior", EVE_TYPE)
{
  using eve::as;
  TTS_ULP_EQUAL (eve::expx2m(T(1)), eve::exp(-T(1)), 0.5);
  TTS_IEEE_EQUAL(eve::expx2m(T(0)), T(1));
  TTS_IEEE_EQUAL(eve::expx2m(T(4)), eve::exp(-T(16)));
  TTS_IEEE_EQUAL(eve::expx2m(T(-4)),eve::exp(-T(16)));
  TTS_IEEE_EQUAL(eve::expx2m(eve::nan(as<T>())) , eve::nan(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2m(eve::inf(as<T>())) , eve::zero(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2m(eve::minf(as<T>())), eve::zero(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2m(T(-0.)), T(1));
  TTS_ULP_EQUAL (eve::expx2m(T(-1)) , eve::exp(-T(1)), 0.5);
}
