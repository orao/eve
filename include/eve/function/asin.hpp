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
  EVE_MAKE_CALLABLE(asin_, asin);

  namespace detail
  {
    template<typename T> inline constexpr auto range_max<tag::asin_(T)> = T(1);
    template<typename T> inline constexpr auto range_min<tag::asin_(T)> = T(-1);
  }
}

#include <eve/module/math/function/generic/asin.hpp>
