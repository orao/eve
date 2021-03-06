//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/saturated/dec.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <type_traits>
#include <algorithm>

TTS_CASE_TPL("Check saturated(eve::dec[condition] return type", EVE_TYPE)
{
  using eve::saturated;

  TTS_EXPR_IS( saturated(eve::dec[ T() ])(T())              , T);
  TTS_EXPR_IS( saturated(eve::dec[ eve::logical<T>() ])(T()), T);
  TTS_EXPR_IS( saturated(eve::dec[ true ])(T())             , T);
}

TTS_CASE_TPL("Check saturated(eve::dec[condition] behavior", EVE_TYPE)
{
  using eve::saturated;

  T tv{2};
  auto t = eve::true_(eve::as<T>());
  auto f = eve::false_(eve::as<T>());

  // All basic TRUE
  TTS_EQUAL(saturated(eve::dec[ 1 ])(tv)     , tv - 1);
  TTS_EQUAL(saturated(eve::dec[ 1.0 ])(tv)   , tv - 1);
  TTS_EQUAL(saturated(eve::dec[ true ])(tv)  , tv - 1);
  TTS_EQUAL(saturated(eve::dec[ t ])(tv)     , tv - 1);

  // All basic FALSE
  TTS_EQUAL(saturated(eve::dec[ 0 ])(tv)     , tv);
  TTS_EQUAL(saturated(eve::dec[ 0.0 ])(tv)   , tv);
  TTS_EQUAL(saturated(eve::dec[ false ])(tv) , tv);
  TTS_EQUAL(saturated(eve::dec[ f ])(tv)     , tv);

  // Mixed case
  eve::as_logical_t<T> m;
  bool k = true;
  #if defined(EVE_SIMD_TESTS)
  for(std::size_t i=0;i<eve::cardinal_v<T>;++i)
  {
    m.set(i, k);
    k = !k;
  }
  #else
  m = k;
  #endif

  TTS_EQUAL(saturated(eve::dec[ m ])(tv) , eve::if_else(m,saturated(eve::dec)(tv), tv) );
}
