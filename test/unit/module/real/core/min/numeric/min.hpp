//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/numeric/min.hpp>
#include <eve/function/numeric.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>

TTS_CASE_TPL("Check eve::numeric(eve::min) return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::numeric(eve::min)(T(0)  , T(0) ) , T);
  TTS_EXPR_IS(eve::numeric(eve::min)(v_t(0) , T(0) ) , T);
  TTS_EXPR_IS(eve::numeric(eve::min)(T(0)  , v_t(0)) , T);
}

TTS_CASE_TPL("Check eve::numeric(eve::min) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::numeric(eve::min)(T(0), T(0)), T(0));
  TTS_EQUAL(eve::numeric(eve::min)(T(0), T(1)), T(0));
  TTS_EQUAL(eve::numeric(eve::min)(T(1), T(0)), T(0));
  TTS_EQUAL(eve::numeric(eve::min)(T(1), T(1)), T(1));

  TTS_EQUAL(eve::numeric(eve::min)(v_t(0), T(0)), T(0));
  TTS_EQUAL(eve::numeric(eve::min)(v_t(0), T(1)), T(0));
  TTS_EQUAL(eve::numeric(eve::min)(v_t(1), T(0)), T(0));
  TTS_EQUAL(eve::numeric(eve::min)(v_t(1), T(1)), T(1));

  TTS_EQUAL(eve::numeric(eve::min)(T(0), v_t(0)), T(0));
  TTS_EQUAL(eve::numeric(eve::min)(T(0), v_t(1)), T(0));
  TTS_EQUAL(eve::numeric(eve::min)(T(1), v_t(0)), T(0));
  TTS_EQUAL(eve::numeric(eve::min)(T(1), v_t(1)), T(1));

  if constexpr(eve::floating_value<T>)
  {
    TTS_IEEE_EQUAL(eve::numeric(eve::min)(eve::nan(eve::as<T>())  , T(1))  , T(1) );
    TTS_IEEE_EQUAL(eve::numeric(eve::min)(eve::nan(eve::as<v_t>()), T(1))  , T(1) );
    TTS_IEEE_EQUAL(eve::numeric(eve::min)(eve::nan(eve::as<T>())  , v_t(1)), T(1) );

    TTS_IEEE_EQUAL(eve::numeric(eve::min)(T(1)  , eve::nan(eve::as<T>())   ), T(1) );
    TTS_IEEE_EQUAL(eve::numeric(eve::min)(v_t(1), eve::nan(eve::as<T>())   ), T(1) );
    TTS_IEEE_EQUAL(eve::numeric(eve::min)(T(1)  , eve::nan(eve::as<v_t>()) ), T(1) );

    TTS_EXPECT(eve::all(eve::is_negative(eve::numeric(eve::min)(T(-0.), T( 0 )))));
    TTS_EXPECT(eve::all(eve::is_negative(eve::numeric(eve::min)(T( 0 ), T(-0.)))));
  }
}
