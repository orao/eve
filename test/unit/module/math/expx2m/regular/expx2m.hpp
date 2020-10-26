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

TTS_CASE_TPL("Check eve::expx2m properties", EVE_TYPE)
{
  auto reg = eve::expx2m;
  using v_t = eve::element_type_t<T>;
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
