//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asecpi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>

TTS_CASE_TPL("Check eve::asecpi return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::asecpi(T(0)), T);
}

TTS_CASE_TPL("Check eve::asecpi behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_IEEE_EQUAL(eve::asecpi(eve::inf(eve::as<T>()))  , T(0.5) );
    TTS_IEEE_EQUAL(eve::asecpi(eve::minf(eve::as<T>())) , T(0.5) );
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::asecpi(eve::nan(eve::as<T>()))  , (eve::nan(eve::as<T>())) );
    TTS_ULP_EQUAL(eve::asecpi(T(-0.)) , eve::nan(eve::as<T>()), 1);
    TTS_ULP_EQUAL(eve::asecpi(T(0))   , eve::nan(eve::as<T>()), 1);
  }

  TTS_ULP_EQUAL(eve::asecpi(T(-2.)), T(2)/3 , 1   );
  TTS_ULP_EQUAL(eve::asecpi(T( 2.)), T(1)/3 , 1   );
  TTS_ULP_EQUAL(eve::asecpi(T(-1.)), T(1)   , 0.5 );
  TTS_ULP_EQUAL(eve::asecpi(T( 1.)), T(0)   , 0.5 );
}
