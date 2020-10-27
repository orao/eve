//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sqr.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/inf.hpp>
#include <eve/function/is_finite.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/all.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <eve/concept/value.hpp>
#include <type_traits>


TTS_CASE_TPL("Check eve::sqr properties", EVE_TYPE)
{
  if(eve::floating_value<T>)
  {
    auto reg = eve::sqr;
    TTS_EXPECT(eve::all(eve::is_not_finite(reg(eve::next(eve::range_max<T>(reg))))));
    TTS_EXPECT(eve::all(eve::is_finite(reg(eve::range_max<T>(reg)))));
  }
  else TTS_EQUAL(0, 0);
}

TTS_CASE_TPL("Check eve::sqr return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sqr(T(0)), T);
}

TTS_CASE_TPL("Check eve::sqr behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::sqr(T(1)), T(1) );
  TTS_EQUAL(eve::sqr(T(2)), T(4) );

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::sqr(static_cast<T>(-2)), T(4));
  }

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::sqr(T(-0.)), T(0));
  }
}
