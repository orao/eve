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
#include <eve/function/properties.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(rec_, rec);
  namespace detail
  {
    template<> inline constexpr auto supports_pedantic<tag::rec_> = true;
    template<> inline constexpr auto supports_raw<tag::rec_> = true;
  }
}

#include <eve/arch.hpp>
#include <eve/module/core/function/generic/rec.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/simd/x86/rec.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/core/function/simd/ppc/rec.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/simd/arm/neon/rec.hpp>
#endif
