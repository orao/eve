//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tanpi.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::restricted(eve::tanpi) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted(eve::tanpi)(T(0)), T);
}

TTS_CASE_TPL("Check eeve::restricted(eve::tanpi) behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted(eve::tanpi)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::tanpi)(eve::inf(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::tanpi)(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()) );
  }

  TTS_EXPECT( eve::all(eve::is_positive(eve::restricted(eve::tanpi)( T( 0 ) )) ));
  TTS_EXPECT( eve::all(eve::is_negative(eve::restricted(eve::tanpi)( T(-0.) )) ));

  TTS_IEEE_EQUAL(eve::restricted(eve::tanpi)(T( 0 )) , T(0));
  TTS_IEEE_EQUAL(eve::restricted(eve::tanpi)(T(-0.)) , T(0));

  TTS_ULP_EQUAL(eve::restricted(eve::tanpi)(T(0.125)) , T(0.41421356237309504880168872420969807856967187537695), 0.5);
  TTS_ULP_EQUAL(eve::restricted(eve::tanpi)(-T(0.125)), T(-0.41421356237309504880168872420969807856967187537695), 0.5);
}
