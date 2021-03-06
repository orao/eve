//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/negate.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>

TTS_CASE_TPL("Check eve::negate return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::negate(T(), T()), T);
}

TTS_CASE_TPL(" negate behaviour", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_EQUAL(eve::negate(eve::inf(eve::as<T>()) , eve::inf(eve::as<T>()) ), eve::inf(eve::as<T>()));
      TTS_EQUAL(eve::negate(eve::minf(eve::as<T>()), eve::minf(eve::as<T>())), eve::inf(eve::as<T>()));

      TTS_IEEE_EQUAL(eve::negate(eve::nan(eve::as<T>()), eve::nan(eve::as<T>()) ), eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(eve::negate(eve::nan(eve::as<T>()), T(0)          ), eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(eve::negate(T(0)         , eve::nan(eve::as<T>()) ), eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(eve::negate(eve::nan(eve::as<T>()), T(0)          ), eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(eve::negate(T(1)         , eve::nan(eve::as<T>()) ), eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(eve::negate(eve::nan(eve::as<T>()), T(1)          ), eve::nan(eve::as<T>()));
    }

    TTS_EQUAL(eve::negate(T(-1), T(-1)), T( 1));
    TTS_EQUAL(eve::negate(T( 1), T( 1)), T( 1));
    TTS_EQUAL(eve::negate(T( 0), T( 0)), T( 0));
    TTS_EQUAL(eve::negate(T( 1), T( 0)), T( 0));
    TTS_EQUAL(eve::negate(T( 2), T(-3)), T(-2));
    TTS_EQUAL(eve::negate(T( 2), T( 3)), T( 2));
  }
  else if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::negate(T(-1), T(-1)), T( 1));
    TTS_EQUAL(eve::negate(T(-1), T( 1)), T(-1));
  }

  TTS_EQUAL(eve::negate(T(1), T(1)), T(1));
  TTS_EQUAL(eve::negate(T(0), T(0)), T(0));
  TTS_EQUAL(eve::negate(T(1), T(0)), T(0));
}
