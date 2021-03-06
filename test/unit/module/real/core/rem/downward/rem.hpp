//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rem.hpp>

TTS_CASE_TPL("Check eve::downward(eve::rem) return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::downward(eve::rem)(T()  , T()  ), T);
  TTS_EXPR_IS(eve::downward(eve::rem)(T()  , v_t()), T);
  TTS_EXPR_IS(eve::downward(eve::rem)(v_t(), T()  ), T);
}

TTS_CASE_TPL("Check eve::downward(eve::rem) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::integral_value<T> && eve::signed_value<T>)
  {
    TTS_EQUAL(eve::downward(eve::rem)(  T(-1),   T(2)), T(1));
    TTS_EQUAL(eve::downward(eve::rem)(v_t(-1),   T(2)), T(1));
    TTS_EQUAL(eve::downward(eve::rem)(  T(-1), v_t(2)), T(1));
    TTS_EQUAL(eve::downward(eve::rem)(  T(-4),   T(3)), T(2));
    TTS_EQUAL(eve::downward(eve::rem)(v_t(-4),   T(3)), T(2));
    TTS_EQUAL(eve::downward(eve::rem)(  T(-4), v_t(3)), T(2));
  }

  TTS_EQUAL(eve::downward(eve::rem)(T{12}, T(4)), T(0));
  TTS_EQUAL(eve::downward(eve::rem)(T( 1), T(2)), T(1));
  TTS_EQUAL(eve::downward(eve::rem)(T( 4), T(3)), T(1));

  TTS_EQUAL(eve::downward(eve::rem)(v_t(12), T(4)), T(0));
  TTS_EQUAL(eve::downward(eve::rem)(v_t( 1), T(2)), T(1));
  TTS_EQUAL(eve::downward(eve::rem)(v_t( 4), T(3)), T(1));

  TTS_EQUAL(eve::downward(eve::rem)(T(12), v_t(4)), T(0));
  TTS_EQUAL(eve::downward(eve::rem)(T( 1), v_t(2)), T(1));
  TTS_EQUAL(eve::downward(eve::rem)(T( 4), v_t(3)), T(1));
}
