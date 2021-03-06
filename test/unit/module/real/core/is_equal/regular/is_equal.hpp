//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_equal.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <eve/concept/value.hpp>
#include <eve/logical.hpp>

TTS_CASE_TPL("Check eve::is_equal return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using eve::logical;

  TTS_EXPR_IS( eve::is_equal(  T()         ,   T()         ) , logical<T>);
  TTS_EXPR_IS( eve::is_equal(  T()         , v_t()         ) , logical<T>);
  TTS_EXPR_IS( eve::is_equal(v_t()         ,   T()         ) , logical<T>);
  TTS_EXPR_IS( eve::is_equal(logical<T>()  , logical<T>()  ) , logical<T>);
  TTS_EXPR_IS( eve::is_equal(logical<T>()  , logical<v_t>()) , logical<T>);
  TTS_EXPR_IS( eve::is_equal(logical<v_t>(), logical<T>()  ) , logical<T>);
}

TTS_CASE_TPL("Check eve::is_equal behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using eve::logical;

  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_equal(eve::nan(eve::as<T>()), eve::nan(eve::as<T>()))   , eve::false_(eve::as<T>()));
    TTS_EQUAL(eve::is_equal(eve::nan(eve::as<T>()), T(4))            , eve::false_(eve::as<T>()));
  }

  TTS_EQUAL(eve::is_equal(T(1)            ,   T(1) )          , eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::is_equal(T(1)            , v_t(1))           , eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::is_equal(T(3)            ,   T(1) )          , eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal(T(3)            , v_t(1))           , eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal(eve::true_(eve::as<T>())  , eve::true_(eve::as<T>()))   , eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::is_equal(eve::true_(eve::as<T>())  , eve::false_(eve::as<T>()))  , eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal(eve::true_(eve::as<T>())  , eve::true_(eve::as<v_t>())) , eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::is_equal(eve::true_(eve::as<T>())  , eve::false_(eve::as<v_t>())), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal(eve::true_(eve::as<v_t>()), eve::true_(eve::as<T>()))   , eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::is_equal(eve::true_(eve::as<v_t>()), eve::false_(eve::as<T>()))  , eve::false_(eve::as<T>()));

  #if defined(EVE_SIMD_TESTS)
  logical<T> mixed1([](auto i, auto) { return i%3 == 0; });
  logical<T> mixed2([](auto i, auto) { return i%2 == 0; });
  logical<T> ref([mixed1,mixed2](auto i, auto) { return mixed1.get(i) == mixed2.get(i); });

  TTS_EQUAL( eve::is_equal(mixed1,mixed2), ref);
  #endif
}
