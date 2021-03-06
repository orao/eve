//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/secd.hpp>
#include <eve/function/secpi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::secd return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::secd(T()), T);
}

TTS_CASE_TPL("Check eve::secd behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::secd(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::secd(eve::inf(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::secd(eve::minf(eve::as<T>())) , eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::secd(T( 0  )) , T(1));
  TTS_IEEE_EQUAL(eve::secd(T(-0.0)) , T(1));

  TTS_ULP_EQUAL(eve::secd( T(  1)  ) , T(1.00015232804390766542842643421257380147891180422143)  , 3);
  TTS_ULP_EQUAL(eve::secd(-T(  1)  ) , T(1.00015232804390766542842643421257380147891180422143)  , 3);
  TTS_ULP_EQUAL(eve::secd( T( 45.0)) , T(1.41421356237309504880168872420969807856967187537694)  , 5);
  TTS_ULP_EQUAL(eve::secd(-T( 45.0)) , T(1.41421356237309504880168872420969807856967187537694)  , 5);
  TTS_ULP_EQUAL(eve::secd( T(500.0)) , T(-1.30540728933227860459313349292274081599849729126374) , 3);
  TTS_ULP_EQUAL(eve::secd(-T(500.0)) , T(-1.30540728933227860459313349292274081599849729126374) , 3);
}
