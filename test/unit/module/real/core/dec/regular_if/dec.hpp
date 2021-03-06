//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/dec.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <type_traits>
#include <algorithm>

TTS_CASE_TPL("Check eve::dec[condition] return type", EVE_TYPE)
{
  TTS_EXPR_IS( eve::dec[ T() ](T())               , T);
  TTS_EXPR_IS( eve::dec[ eve::logical<T>() ](T()) , T);
  TTS_EXPR_IS( eve::dec[ true ](T())              , T);
}

TTS_CASE_TPL("Check eve::dec[condition] behavior", EVE_TYPE)
{
  T tv{2};
  auto t = eve::true_(eve::as<T>());
  auto f = eve::false_(eve::as<T>());

  // All basic TRUE
  TTS_EQUAL(eve::dec[ 1 ](tv)     , eve::dec(tv));
  TTS_EQUAL(eve::dec[ 1.0 ](tv)   , eve::dec(tv));
  TTS_EQUAL(eve::dec[ true ](tv)  , eve::dec(tv));
  TTS_EQUAL(eve::dec[ t ](tv)     , eve::dec(tv));

  // All basic FALSE
  TTS_EQUAL(eve::dec[ 0 ](tv)     , tv);
  TTS_EQUAL(eve::dec[ 0.0 ](tv)   , tv);
  TTS_EQUAL(eve::dec[ false ](tv) , tv);
  TTS_EQUAL(eve::dec[ f ](tv)     , tv);

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

  TTS_EQUAL(eve::dec[ m ](tv) , eve::if_else(m,eve::dec(tv), tv) );
}
