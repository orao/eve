//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(bit_ornot_, bit_ornot);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/bit_ornot.hpp>

#if defined(EVE_HW_ARM)
#  include <eve/module/real/core/function/regular/simd/arm/neon/bit_ornot.hpp>
#endif


