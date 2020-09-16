//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>
#include <eve/function/sinpi.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on sinpi", EVE_TYPE)
{
  auto my_stdsinpi =  tts::vectorize<T>([](auto x){return boost::math::sin_pi(x); });

  eve::rng_producer<T> p(-0.25, 0.25);
  TTS_RANGE_CHECK(p, my_stdsinpi, eve::restricted_(eve::sinpi));
}