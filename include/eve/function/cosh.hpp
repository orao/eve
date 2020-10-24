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
  EVE_MAKE_CALLABLE(cosh_, cosh);
  namespace detail
  {
    // range_max/min
    template<> inline constexpr auto range_max<tag::cosh_(float)>  =  0x1.65a9f8p+6f;       //  89.41598510742188
    template<> inline constexpr auto range_max<tag::cosh_(double)> =  0x1.633ce8fb9f87dp+9;  // 710.4758600739437
    template<> inline constexpr auto range_min<tag::cosh_(float)>  =  -range_max<tag::cosh_(float)>;
    template<> inline constexpr auto range_min<tag::cosh_(double)> =  -range_max<tag::cosh_(double)>;
  }
}

#include <eve/module/math/function/generic/cosh.hpp>
