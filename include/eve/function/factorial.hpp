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
  EVE_MAKE_CALLABLE(factorial_, factorial);
  namespace detail
  {
    template<typename T> inline constexpr auto range_max<tag::factorial_(T)> = T(171);
  }
}

#include <eve/module/combinatorial/function/generic/factorial.hpp>
