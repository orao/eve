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
#include <eve/function/raw.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(acosd_, acosd);

  namespace detail
  {
    template<> inline constexpr auto supports_raw<tag::acosd_> = true;

    template<typename T> inline constexpr auto range_max<tag::acosd_(raw_type, T)> = T(1);
    template<typename T> inline constexpr auto range_max<tag::acosd_(T)> = T(1);

    template<typename T> inline constexpr auto range_min<tag::acosd_(raw_type, T)> = T(-1);
    template<typename T> inline constexpr auto range_min<tag::acosd_(T)> = T(-1);
  }
}

#include <eve/module/math/function/generic/acosd.hpp>
