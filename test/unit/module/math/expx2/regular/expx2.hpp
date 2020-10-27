//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/expx2.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/next.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/concept/value.hpp>
#include <eve/platform.hpp>

#include <eve/concept/value.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::expx2 properties", EVE_TYPE)
{
  auto reg = eve::expx2;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL (reg(eve::prev(eve::range_min<T>(reg))), eve::inf(eve::as<v_t>()), 0.5);
  TTS_EXPECT(eve::is_finite(reg(eve::range_min<T>(reg))));
  TTS_ULP_EQUAL (reg(eve::next(eve::range_max<T>(reg))), eve::inf(eve::as<v_t>()), 0.5);
  TTS_EXPECT(eve::is_finite(reg(eve::range_max<T>(reg))));
}

TTS_CASE_TPL("Check eve::expx2 return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::expx2(T()), T);
}


TTS_CASE_TPL("Check eve::expx2 behavior", EVE_TYPE)
{
  using eve::as;
  TTS_ULP_EQUAL (eve::expx2(T(1)), eve::exp(T(1)), 0.5);
  TTS_IEEE_EQUAL(eve::expx2(T(0)), T(1));
  TTS_IEEE_EQUAL(eve::expx2(T(4)), eve::exp(T(16)));
  TTS_IEEE_EQUAL(eve::expx2(T(-4)),eve::exp(T(16)));
  TTS_IEEE_EQUAL(eve::expx2(eve::nan(as<T>())) , eve::nan(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::inf(as<T>())) , eve::inf(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::minf(as<T>())), eve::inf(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(T(-0.)), T(1));
  TTS_ULP_EQUAL (eve::expx2(T(-1)) , eve::exp(T(1)), 0.5);
}
