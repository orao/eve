//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_not.hpp>
#include <eve/constant/allbits.hpp>

#include <type_traits>

TTS_CASE_TPL("Check eve::bit_not return type", EVE_TYPE)
{
  TTS_EXPR_IS((eve::bit_not[T(1)])(T()), T);
}

TTS_CASE_TPL("Check eve::bit_not behavior", EVE_TYPE)
{
  TTS_IEEE_EQUAL((eve::bit_not[T(1)])(T(0)), (eve::allbits(eve::as<T>())));
  TTS_IEEE_EQUAL((eve::bit_not[T(0)])(T(0)), (T(0)));

  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL ( (eve::bit_not[T(1)])( static_cast<T>(0x1234567890ABCDEFULL))
              , static_cast<T>(0xEDCBA9876F543210ULL)
              );
    TTS_EQUAL ( (eve::bit_not[T(0)])( static_cast<T>(0x1234567890ABCDEFULL))
              , static_cast<T>(0x1234567890ABCDEFULL)
              );

    TTS_EQUAL((eve::bit_not[T(1)])(T( 0)), (T(-1)));
    TTS_EQUAL((eve::bit_not[T(1)])(T(-1)), (T( 0)));
    TTS_EQUAL((eve::bit_not[T(0)])(T( 0)), (T( 0)));
    TTS_EQUAL((eve::bit_not[T(0)])(T(-1)), (T(-1)));
  }
}
