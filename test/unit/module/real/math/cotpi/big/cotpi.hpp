//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cotpi.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/rec.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::cotpi return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::cotpi(T()), T);
}

TTS_CASE_TPL("Check eve::eve::cotpi behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big(eve::cotpi)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::big(eve::cotpi)(eve::inf(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::big(eve::cotpi)(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::big(eve::cotpi)(T( 0 )), eve::rec(T( 0  )));
  TTS_IEEE_EQUAL(eve::big(eve::cotpi)(T(-0.)), eve::rec(T(-0.0)));

  TTS_ULP_EQUAL(eve::big(eve::cotpi)( T( 1)      ) , eve::nan(eve::as<T>()) , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::cotpi)( T(-1)      ) , eve::nan(eve::as<T>()) , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::cotpi)( T(22)      ) , eve::nan(eve::as<T>()) , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::cotpi)(-T(22)      ) , eve::nan(eve::as<T>()) , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::cotpi)( T(100000.5)) , T(0)          , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::cotpi)(-T(100000.5)) , T(0)          , 0.5);
}

