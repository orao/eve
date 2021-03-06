//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/refine_rec.hpp>
#include <eve/function/raw.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> rec_(EVE_SUPPORTS(neon128_)
                                      , raw_type const &
                                      , wide<T, N, ABI> const& v) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();


         if constexpr( cat == category::float32x2) return vrecpe_f32(v);
    else if constexpr( cat == category::float32x4) return vrecpeq_f32(v);
    else if constexpr( current_api >= asimd)
    {
      if constexpr( cat == category::float64x1) return vrecpe_f64(v);
      else if constexpr( cat == category::float64x2) return vrecpeq_f64(v);
    }
    else                                           return map(rec, v);
  }

  template<floating_real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> rec_(EVE_SUPPORTS(neon128_),
                                       wide<T, N, ABI> const &v0) noexcept
  {
      // estimate 1/x with an extra NR step for full precision
      auto a = refine_rec(v0, raw(rec)(v0));
      return refine_rec(v0, a);
  }
}
