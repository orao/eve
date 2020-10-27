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
#include <limits>

namespace eve
{
  EVE_MAKE_CALLABLE(log_, log);
  namespace detail
  {
    // range_min
    template<typename T> inline constexpr T range_min<tag::log_(T)> =
      platform::supports_denormals
      ? std::numeric_limits<T>::denorm_min()
        : std::numeric_limits<T>::min();

    template<> inline constexpr auto supports_pedantic<tag::log_> = true;
  }
}

#include <eve/module/math/function/generic/log.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/math/function/simd/x86/log.hpp>
#endif
