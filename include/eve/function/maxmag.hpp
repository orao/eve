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
  EVE_MAKE_CALLABLE(maxmag_, maxmag);
  namespace detail
  {
    template<> inline constexpr auto supports_pedantic<tag::maxmag_> = true;
    template<> inline constexpr auto supports_numeric<tag::maxmag_> = true;
  }
}

#include <eve/module/core/function/generic/maxmag.hpp>
