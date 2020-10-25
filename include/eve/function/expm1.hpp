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
  EVE_MAKE_CALLABLE(expm1_, expm1);


  namespace detail
  {
    // range_max
    template<> inline constexpr auto range_max<tag::expm1_(float)>  =  0x1.61814ap+6f;       //  88.376259f;
    template<> inline constexpr auto range_max<tag::expm1_(double)> =  0x1.62b7d369a5aa7p+9; // 709.43613930310391;

    template<typename T> inline constexpr T range_max<tag::expm1_(pedantic_type, T)> = range_max<tag::expm1_(T)>;

    // range_min
    template<> inline constexpr auto range_min<tag::expm1_(float)>  =  -0x1.fe2804p+3f;       // -1.5942385e+01f;
    template<> inline constexpr auto range_min<tag::expm1_(double)> =  -0x1.205966f2b4f12p+5; // -3.604365338911715e+01;

    template<typename T> inline constexpr T range_min<tag::expm1_(pedantic_type, T)> = range_min<tag::expm1_(T)>;

    template<> inline constexpr auto supports_pedantic<tag::expm1_> = true;
  }

}

#include <eve/module/math/function/generic/expm1.hpp>
