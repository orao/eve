//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <eve/function/fma.hpp>

#include <type_traits>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, x86_128_> fms_(EVE_SUPPORTS(avx2_),
                                        wide<T, N, x86_128_> const &a,
                                        wide<T, N, x86_128_> const &b,
                                        wide<T, N, x86_128_> const &c) noexcept
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      if constexpr( supports_fma3 )
      {
        if constexpr( std::is_same_v<T, double> )
          return _mm_fmsub_pd(a, b, c);
        else if constexpr( std::is_same_v<T, float> )
          return _mm_fmsub_ps(a, b, c);
      }
      else if constexpr( supports_fma4 )
      {
        if constexpr( std::is_same_v<T, double> )
          return _mm_msub_pd(a, b, c);
        else if constexpr( std::is_same_v<T, float> )
          return _mm_msub_ps(a, b, c);
      }
      else
        return fma(a, b, -c);
    }
    else
    {
      if constexpr( supports_xop )
      {
        if constexpr( std::is_integral_v<T> && sizeof(T) == 2 )
          return _mm_msub_epi16(a, b, c);
        else if constexpr( std::is_integral_v<T> && sizeof(T) == 4 )
          return _mm_msub_epi32(a, b, c);
        else
          return fms_(EVE_RETARGET(cpu_), a, b, c);
      }
      else
        return fms_(EVE_RETARGET(cpu_), a, b, c);
    }
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, x86_256_> fms_(EVE_SUPPORTS(avx2_),
                                        wide<T, N, x86_256_> const &a,
                                        wide<T, N, x86_256_> const &b,
                                        wide<T, N, x86_256_> const &c) noexcept
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      if constexpr( supports_fma3 )
      {
        if constexpr( std::is_same_v<T, double> )
          return _mm256_fmsub_pd(a, b, c);
        else if constexpr( std::is_same_v<T, float> )
          return _mm256_fmsub_ps(a, b, c);
      }
      else if constexpr( supports_fma4 )
      {
        if constexpr( std::is_same_v<T, double> )
          return _mm256_msub_pd(a, b, c);
        else if constexpr( std::is_same_v<T, float> )
          return _mm256_msub_ps(a, b, c);
      }
      else
        return fma(a, b, -c);
    }
    else
      return fma(a, b, -c);
  }
}
