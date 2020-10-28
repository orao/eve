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
  EVE_MAKE_CALLABLE(gcd_, gcd);
  namespace detail
  {
    template<> inline constexpr auto supports_raw<tag::gcd_> = true;
  }
}

#include <eve/module/combinatorial/function/generic/gcd.hpp>
