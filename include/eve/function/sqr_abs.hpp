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
  EVE_MAKE_CALLABLE(sqr_abs_, sqr_abs);
  namespace detail
  {
    // range_max
    template<> inline constexpr auto range_max<tag::sqr_abs_(float)>  =  0x1.fffffep+63f;
    template<> inline constexpr auto range_max<tag::sqr_abs_(double)> =  0x1.fffffffffffffp+511;
    template<> inline constexpr auto range_max<tag::sqr_abs_(std::int8_t)>   =  11;
    template<> inline constexpr auto range_max<tag::sqr_abs_(std::int16_t)>  =  181;
    template<> inline constexpr auto range_max<tag::sqr_abs_(std::int32_t)>  =  46340;
    template<> inline constexpr auto range_max<tag::sqr_abs_(std::int64_t)>  =  3037000499LL;
    template<> inline constexpr auto range_max<tag::sqr_abs_(std::uint8_t)>  =  15;
    template<> inline constexpr auto range_max<tag::sqr_abs_(std::uint16_t)> =  255;
    template<> inline constexpr auto range_max<tag::sqr_abs_(std::uint32_t)> =  65535;
    template<> inline constexpr auto range_max<tag::sqr_abs_(std::uint64_t)> =  4294967296ULL;

    template<signed_value T>    inline constexpr auto range_max<tag::sqr_abs_(T)>  =  -range_max<tag::sqr_abs_(T)>;
  }
}

#include <eve/module/core/function/generic/sqr_abs.hpp>
