//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cotd.hpp>
#include <eve/function/cotpi.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>

TTS_CASE_TPL("Check eve::cotd return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::cotd(T()), T);
}

TTS_CASE_TPL("Check eve::cotd behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::cotd(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::cotd(eve::inf(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::cotd(eve::minf(eve::as<T>())) , eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::cotd(T(0))  , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::cotd(T(-0.)), eve::minf(eve::as<T>()));

  TTS_ULP_EQUAL(eve::cotd( T(  1))   , T(57.289961630759424687278147537112577980217522235144)    , 6);
  TTS_ULP_EQUAL(eve::cotd(-T(  1))   , T(-57.289961630759424687278147537112577980217522235144)   , 6);
  TTS_ULP_EQUAL(eve::cotd( T( 45))   , T(1)                                                      , 6);
  TTS_ULP_EQUAL(eve::cotd(-T( 45))   , T(-1)                                                     , 6);
  TTS_ULP_EQUAL(eve::cotd( T(500.0)) , T(-1.19175359259420995870530807186041933693070040770853)  , 6);
  TTS_ULP_EQUAL(eve::cotd(-T(500.0)) , T(1.19175359259420995870530807186041933693070040770853)   , 6);
}
