//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp2.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/next.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>

#include <cmath>
#include <type_traits>

TTS_CASE_TPL("Check eve::exp properties", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    auto reg = eve::pedantic(eve::exp2);
    using v_t = eve::element_type_t<T>;
    TTS_ULP_EQUAL (reg(eve::prev(eve::range_min<T>(reg))), v_t(0), 0.5);
    TTS_EXPECT(reg(eve::range_min<T>(reg)) >  v_t(0));
    TTS_ULP_EQUAL (reg(eve::range_min<T>(reg)), std::exp2(eve::range_min<v_t>(reg)), 0.5);
    TTS_ULP_EQUAL (reg(eve::next(eve::range_max<T>(reg))), eve::inf(eve::as<v_t>()), 0.5);
    TTS_ULP_EQUAL (reg(eve::range_max<T>(reg)), std::exp2(eve::range_max<v_t>(reg)), 0.5);
  }
  else
  {
    TTS_EQUAL (0, 0);
  }
}

TTS_CASE_TPL("Check eve::pedantic(eve::exp2) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic(eve::exp2)(T(0)), T);
}

TTS_CASE_TPL("Check eve::pedantic(eve::exp2) behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL (eve::pedantic(eve::exp2)(T(1)), T(2), 0.5);
  TTS_IEEE_EQUAL(eve::pedantic(eve::exp2)(T(0)), T(1));

  if constexpr(eve::floating_value<T>)
  {
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_IEEE_EQUAL(eve::pedantic(eve::exp2)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
      TTS_IEEE_EQUAL(eve::pedantic(eve::exp2)(eve::inf(eve::as<T>())) , eve::inf(eve::as<T>()) );
      TTS_IEEE_EQUAL(eve::pedantic(eve::exp2)(eve::minf(eve::as<T>())), T( 0 ) );
    }

    TTS_IEEE_EQUAL(eve::pedantic(eve::exp2)(T(-0.)), T(1));
    TTS_ULP_EQUAL (eve::pedantic(eve::exp2)(T(-1)) , T(0.5), 0.5);
  }

}
