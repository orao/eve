//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rsqrt.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check eve::rsqrt return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::rsqrt(T(0)), T);
}

TTS_CASE_TPL("Check eve::rsqrt behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL(eve::rsqrt(T(1)), T(1  ), 0.5);
  TTS_ULP_EQUAL(eve::rsqrt(T(4)), T(0.5), 0.5);
  TTS_ULP_EQUAL(eve::rsqrt(eve::smallestposval(eve::as<T>())), eve::rec(eve::sqrt(eve::smallestposval(eve::as<T>()))), 0.5);

  if constexpr(eve::floating_value<T> && eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::rsqrt(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()));
    TTS_EQUAL(eve::rsqrt((T(0)))             , eve::inf(eve::as<T>()));
  }
}
