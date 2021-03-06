//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pedantic/lerp.hpp>
#include <eve/function/average.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/eps.hpp>

TTS_CASE_TPL("Check eve::lerp return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic(eve::lerp)(T(), T(), T()), T);
}

TTS_CASE_TPL("Check eve::pedantic(eve::lerp) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL ( eve::pedantic(eve::lerp)(T(12.73), T(27.6666), T(1)), T(27.6666), 0);
  TTS_ULP_EQUAL ( eve::pedantic(eve::lerp)(T(12.73), T(27.6666), T(0)), T(12.73), 0);
  TTS_ULP_EQUAL ( eve::pedantic(eve::lerp)(T(12.73), T(27.6666), T(0.5))
                , eve::average(T(12.73), T(27.6666)),0
                );

  // test monotonicity
  auto e0 = eve::pedantic(eve::lerp)(v_t(1), v_t(2), eve::prev(1 - 10 * eve::eps(eve::as<v_t>())));

  for ( v_t i = 1 - 10 * eve::eps(eve::as<v_t>()); i <= 1 + 10 * eve::eps(eve::as<v_t>());
        i     = eve::next(i)
      )
  {
    auto e1 = eve::pedantic(eve::lerp)(v_t(1), v_t(2), i);
    TTS_LESS_EQUAL(e0, e1);
    e0 = e1;
  }
}
