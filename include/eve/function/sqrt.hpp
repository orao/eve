//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/function/raw.hpp>
#include <type_traits>

namespace eve
{
  namespace tag
  {
    struct sqrt_;
  }

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::sqrt_), [[maybe_unused]] T const &v)
    {
      if constexpr( std::is_integral_v<T> && std::is_signed_v<T> )
      {
        EVE_ASSERT(v >= 0, "[eve::sqrt] - Invalid parameter: " << v);
      }
    }
  }

  EVE_MAKE_CALLABLE(sqrt_, sqrt);

  namespace detail
  {
    // range_min
    template<> inline constexpr auto range_min<tag::sqrt_(float)>  = 0.0f;
    template<> inline constexpr auto range_min<tag::sqrt_(double)> = 0.0;
    template<typename T> inline constexpr auto range_min<tag::sqrt_(raw_type, T)> = range_min<tag::sqrt_(T)>;
    template<> inline constexpr auto supports_raw<tag::sqrt_> = true;
  }
}

#include <eve/arch.hpp>
#include <eve/module/core/function/generic/sqrt.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/simd/x86/sqrt.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/core/function/simd/ppc/sqrt.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/simd/arm/neon/sqrt.hpp>
#endif
