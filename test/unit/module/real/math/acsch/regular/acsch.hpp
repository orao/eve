//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acsch.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check eve::acsch return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::acsch(T(0)), T);
}

TTS_CASE_TPL("Check eve::acsch behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acsch(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acsch(eve::inf(eve::as<T>())) , T(0), 0);
    TTS_ULP_EQUAL(eve::acsch(eve::minf(eve::as<T>())) , T(-0.0), 0);
    TTS_EXPECT(eve::all(eve::is_negative(eve::acsch(eve::minf(eve::as<T>())))));
    TTS_EXPECT(eve::all(eve::is_positive(eve::acsch(eve::inf(eve::as<T>())))));
  }

  TTS_ULP_EQUAL(eve::acsch(T( 0.5)) , T(std::asinh(v_t(2.)))  , 0   );
  TTS_ULP_EQUAL(eve::acsch(T(-0.5)) , T(std::asinh(v_t(-2.)))  , 0   );
  TTS_ULP_EQUAL(eve::acsch(T( 1. )) , T(std::asinh(v_t(1.0)))  , 0.5   );
  TTS_ULP_EQUAL(eve::acsch(T( 2. )) , T(std::asinh(v_t(0.5))), 0.5  );
}
