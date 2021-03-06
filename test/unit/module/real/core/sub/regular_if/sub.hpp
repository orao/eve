//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sub.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <type_traits>
#include <algorithm>

TTS_CASE_TPL("Check eve::sub[condition] return type", EVE_TYPE)
{
  TTS_EXPR_IS( (eve::sub[ T()               ](T(), T())), T);
  TTS_EXPR_IS( (eve::sub[ eve::logical<T>() ](T(), T())), T);
  TTS_EXPR_IS( (eve::sub[ true              ](T(), T())), T);
}

TTS_CASE_TPL("Check eve::sub[condition] behavior", EVE_TYPE)
{
  T tv{5};
  T fv{3};
  auto t = eve::true_(eve::as<T>());
  auto f = eve::false_(eve::as<T>());

  // All basic TRUE
  TTS_EQUAL(eve::sub[ 1     ](tv, fv) , eve::sub(tv,fv));
  TTS_EQUAL(eve::sub[ 1.0   ](tv, fv) , eve::sub(tv,fv));
  TTS_EQUAL(eve::sub[ true  ](tv, fv) , eve::sub(tv,fv));
  TTS_EQUAL(eve::sub[ t     ](tv, fv) , eve::sub(tv,fv));

  // All basic FALSE
  TTS_EQUAL(eve::sub[ 0     ](tv, fv) , tv);
  TTS_EQUAL(eve::sub[ 0.0   ](tv, fv) , tv);
  TTS_EQUAL(eve::sub[ false ](tv, fv) , tv);
  TTS_EQUAL(eve::sub[ f     ](tv, fv) , tv);

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

  TTS_EQUAL(eve::sub[ m ](tv, fv) , eve::if_else(m,eve::sub(tv,fv), tv) );
}
