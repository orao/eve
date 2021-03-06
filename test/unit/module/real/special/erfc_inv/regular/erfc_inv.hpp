//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/erfc_inv.hpp>
#include <boost/math/special_functions/erf.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

// TTS_CASE_TPL("Check eve::erfc_inv return type", EVE_TYPE)
// {
//   TTS_EXPR_IS(eve::erfc_inv(T(0)), T);
// }

TTS_CASE_TPL("Check eve::erfc_inv behavior", EVE_TYPE)
{
  auto eve__erfc_inv =  [](auto x) { return eve::erfc_inv(x); };

 if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve__erfc_inv(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve__erfc_inv(eve::inf(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve__erfc_inv(eve::minf(eve::as<T>())) , eve::nan(eve::as<T>()) );
  }

  TTS_ULP_EQUAL(eve__erfc_inv(T(35)), eve::nan(eve::as<T>()), 0.5);
  TTS_ULP_EQUAL(eve__erfc_inv(T(-35)), eve::nan(eve::as<T>()), 0.5);

 TTS_IEEE_EQUAL(eve__erfc_inv(T( 0 )),eve::inf(eve::as<T>()) );
 TTS_ULP_EQUAL(eve__erfc_inv(T( 0.1 )), T( boost::math::erfc_inv(0.1)), 0.5 );
  TTS_ULP_EQUAL(eve__erfc_inv(T( 0.2 )), T( boost::math::erfc_inv(0.2)), 1.0 );
  TTS_ULP_EQUAL(eve__erfc_inv(T( 0.3 )), T( boost::math::erfc_inv(0.3)), 1 );
  TTS_ULP_EQUAL(eve__erfc_inv(T( 0.5 )), T( boost::math::erfc_inv(0.5)),  1 );
  TTS_ULP_EQUAL(eve__erfc_inv(T( 0.15)), T( boost::math::erfc_inv(0.15)), 0.5 );
  TTS_ULP_EQUAL(eve__erfc_inv(T( 0.75)), T( boost::math::erfc_inv(0.75)), 0.5 );
  TTS_ULP_EQUAL(eve__erfc_inv(T( 1.1 )), T( boost::math::erfc_inv(1.1)), 1.5 );
  TTS_ULP_EQUAL(eve__erfc_inv(T( 1.2 )), T( boost::math::erfc_inv(1.2)), 1.5 );
  TTS_ULP_EQUAL(eve__erfc_inv(T( 1.3 )), T( boost::math::erfc_inv(1.3)), 0.5 );
  TTS_ULP_EQUAL(eve__erfc_inv(T( 1.5 )), T( boost::math::erfc_inv(1.5)),  1 );
  TTS_ULP_EQUAL(eve__erfc_inv(T( 1.15)), T( boost::math::erfc_inv(1.15)), 1 );
  TTS_ULP_EQUAL(eve__erfc_inv(T( 1.75)), T( boost::math::erfc_inv(1.75)), 0.5 );
}
