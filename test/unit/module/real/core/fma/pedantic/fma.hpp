//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pedantic/fma.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/eps.hpp>

TTS_CASE_TPL("Check eve::pedantic(eve::fma) return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::pedantic(eve::fma)(T()   , T()   , T()   ) , T);
  TTS_EXPR_IS(eve::pedantic(eve::fma)(T()   , T()   , v_t() ) , T);
  TTS_EXPR_IS(eve::pedantic(eve::fma)(T()   , v_t() , T()   ) , T);
  TTS_EXPR_IS(eve::pedantic(eve::fma)(T()   , v_t() , v_t() ) , T);
  TTS_EXPR_IS(eve::pedantic(eve::fma)(v_t() , T()   , T()   ) , T);
  TTS_EXPR_IS(eve::pedantic(eve::fma)(v_t() , T()   , v_t() ) , T);
  TTS_EXPR_IS(eve::pedantic(eve::fma)(v_t() , v_t() , T()   ) , T);
}

TTS_CASE_TPL("Check eve::pedantic(eve::fma) behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::pedantic(eve::fma)(T(0), T(0), T(0)), T( 0) );
  TTS_EQUAL(eve::pedantic(eve::fma)(T(0), T(0), T(7)), T( 7) );
  TTS_EQUAL(eve::pedantic(eve::fma)(T(2), T(0), T(7)), T( 7) );
  TTS_EQUAL(eve::pedantic(eve::fma)(T(0), T(5), T(7)), T( 7) );
  TTS_EQUAL(eve::pedantic(eve::fma)(T(2), T(5), T(7)), T(17) );

  if constexpr(eve::floating_value<T>)
  {
    T e = eve::eps(eve::as<T>());
    TTS_EQUAL(eve::pedantic(eve::fma)(eve::inc(e), eve::oneminus(e), T(-1)), -eve::sqr(e) );
  }
}
