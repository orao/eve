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
  EVE_MAKE_CALLABLE(acos_, acos);

  namespace detail
  {
    template<> inline constexpr auto supports_raw<tag::acos_> = true;

    template<typename T> inline constexpr auto range_max<tag::acos_(raw_type, T)> = T(1);
    template<typename T> inline constexpr auto range_max<tag::acos_(T)> = T(1);

    template<typename T> inline constexpr auto range_min<tag::acos_(raw_type, T)> = T(-1);
    template<typename T> inline constexpr auto range_min<tag::acos_(T)> = T(-1);
  }
}

#include <eve/module/math/function/generic/acos.hpp>
