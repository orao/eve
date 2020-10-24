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
  EVE_MAKE_CALLABLE(sinh_, sinh);
  namespace detail
  {
    // range_max/min
    template<> inline constexpr auto range_max<tag::sinh_(float)>  =  0x1.65a9f8p+6f;       //  89.41598510742188
    template<> inline constexpr auto range_max<tag::sinh_(double)> =  0x1.633ce8fb9f87dp+9;  // 710.4758600739437
    template<> inline constexpr auto range_min<tag::sinh_(float)>  =  -range_max<tag::sinh_(float)>;
    template<> inline constexpr auto range_min<tag::sinh_(double)> =  -range_max<tag::sinh_(double)>;
  }
}

#include <eve/module/math/function/generic/sinh.hpp>
