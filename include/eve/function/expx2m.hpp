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
#include <eve/function/pedantic.hpp>
#include <eve/function/regular.hpp>
#include <eve/platform.hpp>
#include <eve/function/properties.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(expx2m_, expx2m);
  namespace detail
  {
    // range_max

    template<> inline constexpr auto range_max<tag::expx2m_(float)>  =   0x1.2b1efp+3f;                      //  9.347526550292969
    template<> inline constexpr auto range_max<tag::expx2m_(double)> =   0x1.a9d9fa9a5cee6p+4;               // 26.61571750925114
// //    template<typename T> inline constexpr T range_max<tag::expx2m_(pedantic_type, T)> = range_max<tag::expx2m_(T)>;
//     template<> inline constexpr auto range_max<tag::expx2m_(pedantic_type, float)>  = 0x1.2b1efp+3f;         //  9.347526550292969
//     template<> inline constexpr auto range_max<tag::expx2m_(pedantic_type, double)> = 0x1.a9d9fa9a5cee6p+4; // 27.2971284039538
//     template<typename T> inline constexpr T range_max<tag::expx2m_(regular_type, T)> = range_max<tag::expx2m_(T)>;

    // range_min
    template<typename T> inline constexpr auto range_min<tag::expx2m_(T)>  =  -range_max<tag::expx2m_(T)>;
    template<typename T> inline constexpr auto range_min<tag::expx2m_(pedantic_type, T)> = -range_max<tag::expx2m_(pedantic_type, T)>;

    template<> inline constexpr auto supports_pedantic<tag::expx2m_> = true;
  }
}

#include <eve/module/math/function/generic/expx2m.hpp>
