//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acoth.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check eve::acoth return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::acoth(T(0)), T);
}

TTS_CASE_TPL("Check eve::acoth behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acoth(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acoth( T( 1.0)), eve::inf(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::acoth( T(-1.0)), eve::minf(eve::as<T>()) , 0);
  }

  TTS_ULP_EQUAL(eve::acoth(T( 2.))  , T(std::atanh(v_t(0.5))) , 0.5 );
  TTS_ULP_EQUAL(eve::acoth(T(-2.))  , T(std::atanh(v_t(-0.5))), 0.5 );
  TTS_ULP_EQUAL(eve::acoth(T( 0. )) ,  eve::nan(eve::as<T>())          , 0   );
}
