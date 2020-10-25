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
#include <eve/detail/assert_utils.hpp>
#include <eve/assert.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/all.hpp>
#include <eve/concept/value.hpp>
#include <type_traits>
#include <eve/platform.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/properties.hpp>


namespace eve
{
  namespace tag { struct exp2_; }

  template<>
  struct supports_optimized_conversion<tag::exp2_> : std::true_type {};

  namespace detail
  {

    template<typename T, typename S>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::exp2_), T const& ,  [[maybe_unused]] S const& s)
    {
      using vt_t = value_type_t<T>;
      if constexpr(std::is_integral_v<vt_t>)
      {
        EVE_ASSERT( all(is_gez(s)),
                    "[eve::exp2] - with integral entries the parameter element(s) must be greater than 0"
                  );
        EVE_ASSERT( all(is_less(s, sizeof(vt_t)*8-std::is_signed_v<vt_t>)),
                    "[eve::exp2]  - overflow caused by too large integral entry"
                  );
      }
    }
  }

  EVE_MAKE_CALLABLE(exp2_, exp2);


  namespace detail
  {
    // range_max
    template<unsigned_value T> constexpr auto range_max<tag::exp2_(T)>  =  sizeof(element_type_t<T>)*8-1;
    template<signed_integral_value T> constexpr auto range_max<tag::exp2_(T)>  =  sizeof(element_type_t<T>)*8-2;

    template<> inline constexpr auto range_max<tag::exp2_(float)>  =  128.0f;
    template<> inline constexpr auto range_max<tag::exp2_(double)> =  1024.0;

    template<typename T> inline constexpr T range_max<tag::exp2_(pedantic_type, T)> = range_max<tag::exp2_(T)>;

    // range_min
    template<> inline constexpr auto range_min<tag::exp2_(float)>  = -126.0f;
    template<> inline constexpr auto range_min<tag::exp2_(double)> = -1022.0;

    template<> inline constexpr auto range_min<tag::exp2_(pedantic_type, float)> =
      platform::supports_denormals ? -149.0f
      : range_min<tag::exp2_(float)>;

    template<> inline constexpr auto range_min<tag::exp2_(pedantic_type, double)> =
      platform::supports_denormals ? -1074.0
      : range_min<tag::exp2_(double)>;

    template<> inline constexpr auto supports_pedantic<tag::exp2_> = true;

    template<typename T> inline constexpr T range_min<tag::exp2_(regular_type, T)> = range_min<tag::exp2_(T)>;
  }

}


#include <eve/module/math/function/generic/exp2.hpp>
