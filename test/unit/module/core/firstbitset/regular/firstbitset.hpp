//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/firstbitset.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check firstbitset return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::firstbitset(T()), T);
}

TTS_CASE_TPL("Check eve::firstbitset behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::firstbitset(T(0)), T(0));
  TTS_EQUAL(eve::firstbitset(T(1)), T(1));
  TTS_EQUAL(eve::firstbitset(T(2)), T(2));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::firstbitset(T(-1)), T(1));
    TTS_EQUAL(eve::firstbitset(T(-2)), T(2));
  }
}