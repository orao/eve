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

namespace eve::detail
{
  template<real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> bit_select_(EVE_SUPPORTS(neon128_),
                                               wide<T, N, ABI> const &m,
                                               wide<T, N, ABI> const &v0,
                                               wide<T, N, ABI> const &v1) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

         if constexpr(cat == category::float64x1) return vbsl_f64(vreinterpret_u64_f64(m), v0, v1);
    else if constexpr(cat == category::float64x2) return vbslq_f64(vreinterpretq_u64_f64(m), v0, v1);
    else if constexpr(cat == category::float32x2) return vbsl_f32(vreinterpret_u32_f32(m), v0, v1);
    else if constexpr(cat == category::int64x1)   return vbsl_s64(vreinterpret_u64_s64(m), v0, v1);
    else if constexpr(cat == category::int32x2)   return vbsl_s32(vreinterpret_u32_s32(m), v0, v1);
    else if constexpr(cat == category::int16x4)   return vbsl_s16(vreinterpret_u16_s16(m), v0, v1);
    else if constexpr(cat == category::int8x8)    return vbsl_s8(vreinterpret_u8_s8(m), v0, v1);
    else if constexpr(cat == category::uint64x1)  return vbsl_u64(m, v0, v1);
    else if constexpr(cat == category::uint32x2)  return vbsl_u32(m, v0, v1);
    else if constexpr(cat == category::uint16x4)  return vbsl_u16(m, v0, v1);
    else if constexpr(cat == category::uint8x8)   return vbsl_u8(m, v0, v1);
    else if constexpr(cat == category::float32x4) return vbslq_f32(vreinterpretq_u32_f32(m), v0, v1);
    else if constexpr(cat == category::int64x2)   return vbslq_s64(vreinterpretq_u64_s64(m), v0, v1);
    else if constexpr(cat == category::int32x4)   return vbslq_s32(vreinterpretq_u32_s32(m), v0, v1);
    else if constexpr(cat == category::int16x8)   return vbslq_s16(vreinterpretq_u16_s16(m), v0, v1);
    else if constexpr(cat == category::int8x16)   return vbslq_s8(vreinterpretq_u8_s8(m), v0, v1);
    else if constexpr(cat == category::uint64x2)  return vbslq_u64(m, v0, v1);
    else if constexpr(cat == category::uint32x4)  return vbslq_u32(m, v0, v1);
    else if constexpr(cat == category::uint16x8)  return vbslq_u16(m, v0, v1);
    else if constexpr(cat == category::uint8x16)  return vbslq_u8(m, v0, v1);
  }
}
