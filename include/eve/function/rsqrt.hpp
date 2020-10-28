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

namespace eve
{
  EVE_MAKE_CALLABLE(rsqrt_, rsqrt);
  namespace detail
  {
    template<> inline constexpr auto supports_pedantic<tag::rsqrt_> = true;

    // range_min
    template<> inline constexpr auto range_min<tag::rsqrt_(float)>  = 0.0f;
    template<> inline constexpr auto range_min<tag::rsqrt_(double)> = 0.0;
    template<typename T> inline constexpr T range_min<tag::rsqrt_(pedantic_type, T)> = range_min<tag::rsqrt_(T)>;
    template<> inline constexpr auto supports_raw<tag::rsqrt_> = true;
  }
}

#include <eve/arch.hpp>
#include <eve/module/core/function/generic/rsqrt.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/simd/x86/rsqrt.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/core/function/simd/ppc/rsqrt.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/simd/arm/neon/rsqrt.hpp>
#endif
