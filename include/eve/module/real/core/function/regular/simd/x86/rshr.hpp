//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<integral_real_scalar_value T, integral_real_scalar_value I, typename N>
  EVE_FORCEINLINE auto rshr_(EVE_SUPPORTS(avx_),
                             wide<T, N, x86_128_> const &a0,
                             wide<I, N, x86_128_> const &a1) noexcept
  {
    if constexpr(supports_xop)
    {
      using si_t = wide<as_integer_t<I, signed>, N, x86_128_>;
      auto sa1   = -bit_cast(a1, as_<si_t>{});
      if(std::is_signed_v<I>)
      {
        if constexpr(sizeof(T) == 1)
        {
          return _mm_sha_epi8(a0, sa1);
        }
        else if constexpr(sizeof(T) == 2)
        {
          return _mm_sha_epi16(a0, sa1);
        }
        else if constexpr(sizeof(T) == 4)
        {
          return _mm_sha_epi32(a0, sa1);
        }
        else if constexpr(sizeof(T) == 8)
        {
          return _mm_sha_epi64(a0, sa1);
        }
      }
      else
      {
        auto ssa1 = -a1;
        if constexpr(sizeof(T) == 1)
        {
          return _mm_shl_epi8(a0, ssa1);
        }
        else if constexpr(sizeof(T) == 2)
        {
          return _mm_shl_epi16(a0, ssa1);
        }
        else if constexpr(sizeof(T) == 4)
        {
          return _mm_shl_epi32(a0, ssa1);
        }
        else if constexpr(sizeof(T) == 8)
        {
          return _mm_shl_epi64(a0, ssa1);
        }
      }
    }
    else
    {
      return map(eve::rshr, a0, a1);//TODO pas g�nial
    }
  }
}
