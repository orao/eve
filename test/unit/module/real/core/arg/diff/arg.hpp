//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/detail/diff_div.hpp>
#include <eve/function/diff/arg.hpp>
#include <eve/function/sqrt.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(arg) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff(eve::arg)(T()), T);
  }
}

TTS_CASE_TPL("Check eve::diff(eve::arg) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using elt_t = eve::element_type_t<T>;
    auto ulp =  (sizeof(elt_t) == 4) ? 1.0e4 : 1.0e8;
    auto df = [](auto f, auto x){return eve::detail::centered_diffdiv(f, x); };
    TTS_ULP_EQUAL(eve::diff(eve::arg)(T{0.25}), df(eve::arg, T(0.25))  , ulp);
    TTS_ULP_EQUAL(eve::diff(eve::arg)(T{1}), df(eve::arg, T(1))        , ulp);
    TTS_ULP_EQUAL(eve::diff(eve::arg)(T{-0.25}), df(eve::arg, T(-0.25)), ulp);
  }
}
