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

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/function/properties.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(log1p_, log1p);
   namespace detail
   {
     // range_min
     template<> inline constexpr auto range_min<tag::log1p_(float)>  = -0x1.fffffep-1f;
     template<> inline constexpr auto range_min<tag::log1p_(double)> = -0x1.fffffffffffffp-1;

     template<> inline constexpr auto supports_pedantic<tag::log1p_> = true;
   }
}

#include <eve/module/math/function/generic/log1p.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/math/function/simd/x86/log1p.hpp>
#endif
