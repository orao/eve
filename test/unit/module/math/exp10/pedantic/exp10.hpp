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

TTS_CASE_TPL("Check pedantic(eve::exp) properties", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    auto ped = eve::pedantic(eve::exp10);
    using v_t = eve::element_type_t<T>;
    TTS_ULP_EQUAL (ped(eve::prev(eve::range_min<T>(ped))), v_t(0), 0.5);
    TTS_EXPECT(ped(eve::range_min<T>(ped)) >  v_t(0));
//    TTS_ULP_EQUAL (ped(eve::range_min<T>(ped)), std::exp2(eve::range_min<v_t>(ped)), 0.5);
    TTS_ULP_EQUAL (ped(eve::next(eve::range_max<T>(ped))), eve::inf(eve::as<v_t>()), 0.5);
//    TTS_ULP_EQUAL (ped(eve::range_max<T>(ped)), std::exp2(eve::range_max<v_t>(ped)), 0.5);
    TTS_EXPECT(eve::is_finite(ped(eve::range_max<T>(ped))));
  }
  else
  {
    TTS_EQUAL (0, 0);
  }
}

TTS_CASE_TPL("Check eve::pedantic(eve::exp10) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic(eve::exp10)(T(0)), T);
}

TTS_CASE_TPL("Check eve::pedantic(eve::exp10) behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL ( eve::pedantic(eve::exp10)(T(1)), T(10), 0.5);
  TTS_IEEE_EQUAL( eve::pedantic(eve::exp10)(T(0)), T(1));

  if constexpr(eve::floating_value<T>)
  {
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_IEEE_EQUAL(eve::pedantic(eve::exp10)(eve::nan(eve::as<T>())) , (eve::nan(eve::as<T>())) );
      TTS_IEEE_EQUAL(eve::pedantic(eve::exp10)(eve::inf(eve::as<T>())) , (eve::inf(eve::as<T>())) );
      TTS_IEEE_EQUAL(eve::pedantic(eve::exp10)(eve::minf(eve::as<T>())), (T( 0 )) );
    }

    TTS_ULP_EQUAL ( eve::pedantic(eve::exp10)(T(-1)) , T(0.1), 0.5);
    TTS_IEEE_EQUAL( eve::pedantic(eve::exp10)(T(-0.)), T(1));
  }
}
