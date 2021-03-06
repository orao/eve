//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acscd.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::acscd return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::acscd(T(0)), T);
}

TTS_CASE_TPL("Check eve::acscd behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acscd(T(0))  , eve::nan(eve::as<T>()), 1);
    TTS_ULP_EQUAL(eve::acscd(T(-0.)), eve::nan(eve::as<T>()), 1);
    TTS_IEEE_EQUAL(eve::acscd(eve::nan(eve::as<T>())) , (eve::nan(eve::as<T>())) );
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_IEEE_EQUAL(eve::acscd(eve::inf(eve::as<T>()))  , (T(0)) );
    TTS_IEEE_EQUAL(eve::acscd(eve::minf(eve::as<T>())) , (T(0)) );
  }

  TTS_ULP_EQUAL(eve::acscd(T(-2.)),  -T(30), 1  );
  TTS_ULP_EQUAL(eve::acscd(T( 2.)),   T(30), 1  );
  TTS_ULP_EQUAL(eve::acscd(T(-1.)),  -T(90), 0.5);
  TTS_ULP_EQUAL(eve::acscd(T( 1.)),   T(90), 0.5);
}
