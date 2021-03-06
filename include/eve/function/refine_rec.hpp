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
  EVE_MAKE_CALLABLE(refine_rec_, refine_rec);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/refine_rec.hpp>

#if defined(EVE_HW_ARM)
#  include <eve/module/real/core/function/regular/simd/arm/neon/refine_rec.hpp>
#endif

