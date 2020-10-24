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
  EVE_MAKE_CALLABLE(exp_, exp);

  namespace detail
  {
    // range_max
    template<> inline constexpr auto range_max<tag::exp_(float)>  =  0x1.61814ap+6f;       //  88.376259f;
    template<> inline constexpr auto range_max<tag::exp_(double)> =  0x1.62b7d369a5aa7p+9; // 709.43613930310391;

    template<typename T> inline constexpr T range_max<tag::exp_(pedantic_type, T)> = range_max<tag::exp_(T)>;

    // range_min
    template<> inline constexpr auto range_min<tag::exp_(float)>  = -0x1.5d814ap+6f;       //  -87.376259f;
    template<> inline constexpr auto range_min<tag::exp_(double)> = -0x1.6232bdd7abc97p+9; // -708.39641853226420;

    template<> inline constexpr auto range_min<tag::exp_(pedantic_type, float)> =
      platform::supports_denormals ? -0x1.9fe368p+6f        // -103.972084f;
                                   : range_min<tag::exp_(float)>;

    template<> inline constexpr auto range_min<tag::exp_(pedantic_type, double)> =
      platform::supports_denormals ? -0x1.74910d52d3051p+9 // -745.1332191019413358
                                   : range_min<tag::exp_(double)>;

    template<> inline constexpr auto supports_pedantic<tag::exp_> = true;
    template<typename T> inline constexpr T range_min<tag::exp_(regular_type, T)> = range_min<tag::exp_(T)>;
  }
}

#include <eve/module/math/function/generic/exp.hpp>
