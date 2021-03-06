//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/wide.hpp>
#include <eve/logical.hpp>

TTS_CASE_TPL("Check slicing for arithmetic wide", EVE_TYPE)
{
  if constexpr( EVE_CARDINAL > 1 )
  {
    using eve::wide;

    using split_t = typename eve::cardinal_t<T>::split_type;
    T                         simd    ([](auto i, auto) { return 1 + i; });
    wide<EVE_VALUE, split_t>  ref_low ([](auto i, auto) { return 1 + i; });
    wide<EVE_VALUE, split_t>  ref_high([](auto i, auto) { return EVE_CARDINAL / 2 + 1 + i; });

    auto [ low, high ] = simd.slice();

    TTS_EQUAL(low, ref_low);
    TTS_EQUAL(simd.slice(eve::lower_), ref_low);
    TTS_EQUAL(high, ref_high);
    TTS_EQUAL(simd.slice(eve::upper_), ref_high);
  }
  else
  {
    TTS_PASS("Small type don't need to be sliced");
  }
}

TTS_CASE_TPL("Check slicing for arithmetic wide", EVE_TYPE)
{
  if constexpr( EVE_CARDINAL > 1 )
  {
    using eve::logical;
    using eve::wide;

    using split_t = typename eve::cardinal_t<T>::split_type;
    logical<T>                        simd    ([](auto i, auto c) { return i < int(c) / 2; });
    logical<wide<EVE_VALUE, split_t>> ref_low ([](auto i, auto  ) { return i % 2 < 2; });
    logical<wide<EVE_VALUE, split_t>> ref_high([](auto i, auto  ) { return i % 2 > 3; });

    auto [ low, high ] = simd.slice();

    TTS_EQUAL(low, ref_low);
    TTS_EQUAL(simd.slice(eve::lower_), ref_low);
    TTS_EQUAL(high, ref_high);
    TTS_EQUAL(simd.slice(eve::upper_), ref_high);
  }
  else
  {
    TTS_PASS("Small type don't need to be sliced");
  }
}
