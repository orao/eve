//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fnma.hpp>

TTS_CASE_TPL("Check eve::fnma return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::fnma(T()   , T()   , T()   ) , T);
  TTS_EXPR_IS(eve::fnma(T()   , T()   , v_t() ) , T);
  TTS_EXPR_IS(eve::fnma(T()   , v_t() , T()   ) , T);
  TTS_EXPR_IS(eve::fnma(T()   , v_t() , v_t() ) , T);
  TTS_EXPR_IS(eve::fnma(v_t() , T()   , T()   ) , T);
  TTS_EXPR_IS(eve::fnma(v_t() , T()   , v_t() ) , T);
  TTS_EXPR_IS(eve::fnma(v_t() , v_t() , T()   ) , T);
}

TTS_CASE_TPL("Check eve::fnma behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::fnma(T(0), T(0), T(0)), T(0) );
  TTS_EQUAL(eve::fnma(T(0), T(0), T(7)), T(7) );
  TTS_EQUAL(eve::fnma(T(2), T(0), T(7)), T(7) );
  TTS_EQUAL(eve::fnma(T(0), T(5), T(7)), T(7) );
  TTS_EQUAL(eve::fnma(T(2), T(5), T(7)), static_cast<T>(-3));
}
