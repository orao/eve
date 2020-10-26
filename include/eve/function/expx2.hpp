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

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(expx2_, expx2);
  namespace detail
  {
    // range_max

    template<> inline constexpr auto range_max<tag::expx2_(float)>  =  0x1.2cd3e2p+3f;         // 9.400864601135254f;
    template<> inline constexpr auto range_max<tag::expx2_(double)> =  0x1.aa29f3f75bd2ep+4;  //26.6352424299668;
    template<typename T> inline constexpr T range_max<tag::expx2_(pedantic_type, T)> = range_max<tag::expx2_(T)>;

    // range_min
    template<typename T> inline constexpr auto range_min<tag::expx2_(T)>  =  -range_max<tag::expx2_(T)>;
  }
}

#include <eve/module/math/function/generic/expx2.hpp>
