//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/countr_zero.hpp>

TTS_CASE_TPL("Check countr_zero return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::countr_zero(T()), T);
}

TTS_CASE_TPL("Check eve::countr_zero behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::countr_zero(T(0)), T(sizeof(v_t) * 8));
  TTS_EQUAL(eve::countr_zero(T(3)), T(0));
  TTS_EQUAL(eve::countr_zero(T(8)), T(3));
  TTS_EQUAL(eve::countr_zero(T(6)), T(1));
  TTS_EQUAL(eve::countr_zero(T(9)), T(0));
}
