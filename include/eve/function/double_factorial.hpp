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
  EVE_MAKE_CALLABLE(double_factorial_, double_factorial);
  namespace detail
  {
    template<> inline constexpr auto range_max<tag::double_factorial_(std::uint8_t)> = std::uint8_t(255);
    template<typename T> inline constexpr auto range_max<tag::double_factorial_(T)> = T(300);
  }
}

#include <eve/module/combinatorial/function/generic/double_factorial.hpp>
