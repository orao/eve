//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp10.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/next.hpp>
#include <eve/function/is_finite.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>

#include <cmath>
#include <eve/function/average.hpp>

TTS_CASE_TPL("Check eve::exp properties", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    auto reg = eve::exp10;
    using v_t = eve::element_type_t<T>;
    TTS_ULP_EQUAL (reg(eve::prev(eve::range_min<T>(reg))), v_t(0), 0.5);
    TTS_EXPECT(reg(eve::range_min<T>(reg)) >  v_t(0));
    TTS_ULP_EQUAL (reg(eve::next(eve::range_max<T>(reg))), eve::inf(eve::as<v_t>()), 0.5);
    TTS_EXPECT(eve::is_finite(reg(eve::range_max<T>(reg))));
  }
  else
  {
    TTS_EQUAL (0, 0);
  }
}

TTS_CASE_TPL("Check eve::exp10 return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::exp10(T(0)), T);
}

TTS_CASE_TPL("Check eve::exp10 behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL ( eve::exp10(T(1)), T(10), 0.5);
  TTS_IEEE_EQUAL( eve::exp10(T(0)), T(1));

  if constexpr(eve::floating_value<T>)
  {
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_IEEE_EQUAL(eve::exp10(eve::nan(eve::as<T>())) , (eve::nan(eve::as<T>())) );
      TTS_IEEE_EQUAL(eve::exp10(eve::inf(eve::as<T>())) , (eve::inf(eve::as<T>())) );
      TTS_IEEE_EQUAL(eve::exp10(eve::minf(eve::as<T>())), (T( 0 )) );
    }

    TTS_ULP_EQUAL ( eve::exp10(T(-1)) , T(0.1), 0.5);
    TTS_IEEE_EQUAL( eve::exp10(T(-0.)), T(1));
  }
}
