//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/nthroot.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>

TTS_CASE_TPL("Check eve::nthroot) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::nthroot(T(0), T(0)), T);
}

TTS_CASE_TPL("Check eve::nthroot) behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL(eve::nthroot(T(0), T(-1)), eve::inf(eve::as<T>()), 0);
  TTS_ULP_EQUAL(eve::nthroot(-T(0), T(-2)), eve::nan(eve::as<T>()), 0);
  TTS_ULP_EQUAL(eve::nthroot(T(0), T(-2)), eve::inf(eve::as<T>()), 0);
  TTS_ULP_EQUAL(eve::nthroot(T(0),  2),  T(0), 0);
  TTS_ULP_EQUAL(eve::nthroot(-T(0), 2),  eve::nan(eve::as<T>()), 0);
  TTS_ULP_EQUAL(eve::nthroot(eve::inf(eve::as<T>()), T(4) ),  eve::inf(eve::as<T>()), 0);
  TTS_ULP_EQUAL(eve::nthroot(eve::inf(eve::as<T>()), T(-4) ),  T( 0 ), 0);
  TTS_ULP_EQUAL(eve::nthroot(eve::minf(eve::as<T>()), T(4) ),  eve::nan(eve::as<T>()), 0);
  TTS_ULP_EQUAL(eve::nthroot(eve::minf(eve::as<T>()), T(3) ),  eve::minf(eve::as<T>()), 0);
  TTS_ULP_EQUAL(eve::nthroot(T(64), 3),  T(4), 0.5);
  TTS_EQUAL(eve::nthroot(T(8),-3), T(0.5));
  TTS_EQUAL(eve::nthroot(T(8),3) , T(2)    );
  TTS_EQUAL(eve::nthroot(T(8),3u), T(2)    );
}
