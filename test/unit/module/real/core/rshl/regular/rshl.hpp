//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rshl.hpp>
#include <eve/constant/allbits.hpp>

TTS_CASE_TPL("Check eve::rshl return type", EVE_TYPE)
{
  using i_t = eve::as_integer_t<T, signed>;
  using u_t = eve::as_integer_t<T, unsigned>;

  TTS_EXPR_IS(eve::rshl(  T(),  T()),   T);
  TTS_EXPR_IS(eve::rshl(  T(),i_t()),   T);
  TTS_EXPR_IS(eve::rshl(  T(),u_t()),   T);
  TTS_EXPR_IS(eve::rshl(i_t(),  T()), i_t);
  TTS_EXPR_IS(eve::rshl(u_t(),  T()), u_t);
}

TTS_CASE_TPL("Check eve::rshl behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::rshl(T(1), T(4)), (T(16)));

  TTS_EQUAL(eve::rshl(T(1),  4), (T(16)));
  TTS_EQUAL(eve::rshl(T(3), -1), (T( 1)));
  TTS_EQUAL(eve::rshl(T(0),  3), (T( 0)));
  TTS_EQUAL(eve::rshl(T(8), -2), (T( 2)));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::rshl(eve::allbits(eve::as<T>()),  1), T(-2)             );
    TTS_EQUAL(eve::rshl(eve::allbits(eve::as<T>()), -1), eve::allbits(eve::as<T>()) );
  }
  else
  {
    TTS_EQUAL(eve::rshl(eve::allbits(eve::as<T>()),  1), eve::allbits(eve::as<T>()) - 1 );
    TTS_EQUAL(eve::rshl(eve::allbits(eve::as<T>()), -1), eve::allbits(eve::as<T>())/2   );
  }
}
