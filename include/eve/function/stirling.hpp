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
  EVE_MAKE_CALLABLE(stirling_, stirling);

  namespace detail
  {
    // range_min
    template<> inline constexpr auto range_min<tag::stirling_(float)>  = 0.0f;
    template<> inline constexpr auto range_min<tag::stirling_(double)> = 0.0;

    template<> inline constexpr auto range_max<tag::stirling_(float)>  = 0x1.1851e6p+5f;  //35.0399895f;
    template<> inline constexpr auto range_max<tag::stirling_(double)> = 172.0;
  }
}

#include <eve/module/special/function/generic/stirling.hpp>
