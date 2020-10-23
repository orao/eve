//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/is_denormal.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check eve::exp return properties", EVE_TYPE)
{
  {
    auto reg = eve::exp;
    using v_t = eve::element_type_t<T>;
    TTS_ULP_EQUAL (reg(eve::prev(eve::range_min<T>(reg))), v_t(0), 0.5);
    TTS_ULP_EQUAL (reg(eve::range_min<T>(reg)), std::exp(eve::range_min<v_t>(reg)), 0.5);
  }
  {
    auto ped = eve::pedantic(eve::exp);
    using v_t = eve::element_type_t<T>;
    TTS_ULP_EQUAL (ped(eve::prev(eve::range_min<T>(ped))), v_t(0), 0.5);
    TTS_ULP_EQUAL (ped(eve::range_min<T>(ped)), std::exp(eve::range_min<v_t>(ped)), 0.5);
  }

  {
    auto ped = eve::pedantic(eve::exp);
    using v_t = eve::element_type_t<T>;
    TTS_ULP_EQUAL (ped(eve::next(eve::range_max<T>(ped))), eve::inf(eve::as<v_t>()), 0.5);
    TTS_ULP_EQUAL (ped(eve::range_max<T>(ped)), std::exp(eve::range_max<v_t>(ped)), 0.5);
//     std::cout << "prev " << std::hexfloat << eve::prev(eve::range_max<T>(ped), 100) <<  " -> " << std::defaultfloat << ped(eve::prev(eve::range_max<T>(ped), 100)) << std::endl;
//     std::cout << "prev " << std::hexfloat << eve::prev(eve::range_max<T>(ped), 2) <<  " -> " << std::defaultfloat << ped(eve::prev(eve::range_max<T>(ped), 2)) << std::endl;
//     std::cout << "prev " << std::hexfloat << eve::prev(eve::range_max<T>(ped)) <<  " -> " << std::defaultfloat << ped(eve::prev(eve::range_max<T>(ped))) << std::endl;
//     std::cout << "val  " << std::hexfloat << eve::range_max<T>(ped) <<  " -> " << std::defaultfloat << ped(eve::range_max<T>(ped)) << " <- " << eve::range_max<T>(ped) << std::endl;
//     std::cout << "next " << std::hexfloat << eve::next(eve::range_max<T>(ped)) <<  " -> " << std::defaultfloat << ped(eve::next(eve::range_max<T>(ped))) << std::endl;
//     std::cout << "next " << std::hexfloat << eve::next(eve::range_max<T>(ped), 2) <<  " -> " << std::defaultfloat << ped(eve::next(eve::range_max<T>(ped), 2)) << std::endl;
//     std::cout << "next " << std::hexfloat << eve::next(eve::range_max<T>(ped), 3) <<  " -> " << std::defaultfloat << ped(eve::next(eve::range_max<T>(ped), 3)) << std::endl;
//     std::cout << "next " << std::hexfloat << eve::next(eve::range_max<T>(ped), 100) <<  " -> " << std::defaultfloat << ped(eve::next(eve::range_max<T>(ped), 30)) << std::endl;
  }
}

TTS_CASE_TPL("Check eve::exp return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::exp(T(0)), T);
}

TTS_CASE_TPL("Check eve::exp behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::exp(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::exp(eve::inf(eve::as<T>())) , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::exp(eve::minf(eve::as<T>())), T( 0 ) );
  }

  TTS_ULP_EQUAL(eve::exp(T(1)), T(std::exp(v_t(1))), 0.5);
  TTS_ULP_EQUAL(eve::exp(T(-1)),T(std::exp(v_t(-1))), 0.5);

  TTS_IEEE_EQUAL( eve::exp(T( 0.)), T(1));
  TTS_IEEE_EQUAL( eve::exp(T(-0.)), T(1));
}
