//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinh.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/next.hpp>
#include <eve/function/is_finite.hpp>
#include <eve/function/average.hpp>
#include <eve/platform.hpp>
TTS_CASE_TPL("Check eve::exp properties", EVE_TYPE)
{
  {
    auto reg = eve::sinh;
    using v_t = eve::element_type_t<T>;
    TTS_ULP_EQUAL (reg(eve::next(eve::range_max<T>(reg))), eve::inf(eve::as<v_t>()), 0.5);
    TTS_ULP_EQUAL (reg(eve::range_max<T>(reg)), std::sinh(eve::range_max<v_t>(reg)), 0.5);
    TTS_ULP_EQUAL (reg(eve::prev(eve::range_min<T>(reg))), eve::minf(eve::as<v_t>()), 0.5);
    TTS_ULP_EQUAL (reg(eve::range_min<T>(reg)), std::sinh(eve::range_min<v_t>(reg)), 0.5);
    {
      auto vmin = eve::range_max<T>(reg)*v_t(0.9);
      auto vmax = eve::range_max<T>(reg)*v_t(1.1);
      if(eve::is_finite(reg(vmin)) && !eve::is_finite(reg(vmax)))
      {
        while(true)
        {
          auto v =  eve::average(vmax, vmin);
          if (eve::is_finite(reg(v))) vmin = v;  else vmax = v;
//         std::cout << "vmax " << vmax <<  std::endl;
//         std::cout << "vmin " << vmin <<  std::endl;
//         std::cout << "vmin > vmax   " << (vmin > vmax) <<  std::endl;
          if(vmax >=   eve::prev(vmin))
          {
            std::cout << std::hexfloat << eve::next(v) << " -> " << reg(eve::next(v)) << " -> " << std::defaultfloat << std::setprecision(16) << eve::next(v) << std::endl;
            std::cout << std::hexfloat << v << " -> " << reg(v) << std::endl;
            std::cout << std::hexfloat << eve::prev(v) << " -> " << reg(eve::prev(v)) << " -> " << std::defaultfloat << std::setprecision(16) << eve::next(v) << std::endl;
            break;
          }
        }
      }
      else
        std::cout << "zut" << std::endl;
    }
    {
      auto vmax = eve::range_min<T>(reg)*v_t(0.9);
      auto vmin = eve::range_min<T>(reg)*v_t(1.1);
      if(eve::is_finite(reg(vmax)) && !eve::is_finite(reg(vmin)))
      {
        while(true)
        {
          auto v =  eve::average(vmin, vmax);
          if (eve::is_finite(reg(v))) vmax = v;  else vmin = v;
//         std::cout << "vmin " << vmin <<  std::endl;
//         std::cout << "vmax " << vmax <<  std::endl;
//         std::cout << "vmax > vmin   " << (vmax > vmin) <<  std::endl;
          if(vmin >=   eve::prev(vmax))
          {
            std::cout << std::hexfloat << eve::next(v) << " -> " << reg(eve::next(v)) << " -> " << std::defaultfloat << std::setprecision(16) << eve::next(v) << std::endl;
            std::cout << std::hexfloat << v << " -> " << reg(v) << std::endl;
            std::cout << std::hexfloat << eve::prev(v) << " -> " << reg(eve::prev(v)) << " -> " << std::defaultfloat << std::setprecision(16) << eve::next(v) << std::endl;
            break;
          }
        }
      }
      else
        std::cout << "zut" << std::endl;
    }
  }
}


TTS_CASE_TPL("Check eve::sinh return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sinh(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::sinh behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::sinh(eve::nan(eve::as<T>())) , (eve::nan(eve::as<T>())) );
    TTS_IEEE_EQUAL(eve::sinh(eve::inf(eve::as<T>())) , (eve::inf(eve::as<T>())) );
    TTS_IEEE_EQUAL(eve::sinh(eve::minf(eve::as<T>())), (eve::minf(eve::as<T>())) );
  }
  TTS_EXPECT(eve::all(eve::is_negative(eve::sinh(T(-0.)))) );
  TTS_EXPECT(eve::all(eve::is_positive(eve::sinh(T(0))))            );

  v_t ovflimit =  eve::Ieee_constant<v_t,0x42B0C0A4U, 0x40862E42FEFA39EFULL>();
  std::array<v_t, 10> a = {v_t(1), v_t(-1), v_t(0), v_t(-0.0), v_t(10), v_t(-10)
                             , eve::maxlog(eve::as<v_t>()), ovflimit/2, ovflimit, 2*ovflimit};

  for(size_t i=0; i < a.size(); ++i)
  {
    auto sh  = eve::sinh(T(a[i]));
    v_t sh1 = std::sinh(double(a[i]));
    TTS_ULP_EQUAL(sh, (T(sh1)), 0.5);
  }
}
