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
#include <eve/assert.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/all.hpp>
//#include <eve/constant/maxlog10.hpp>
#include <type_traits>
#include <eve/platform.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/properties.hpp>

namespace eve
{
  namespace tag { struct exp10_; }

  namespace detail
  {
    template<typename T, typename S>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::exp10_), T const&, [[maybe_unused]] S const& s)
    {
      using vt_t = value_type_t<T>;
      if constexpr(std::is_integral_v<vt_t>)
      {
        EVE_ASSERT( all(is_gez(s)),
                    "[eve::exp10] - with integral entries the parameter element(s) must be greater then 0"
                  );
        EVE_ASSERT( all(is_less(s, max_range<T>(exp10))),
                    "[eve::exp10]  - overflow caused by too large integral entry"
                  );
      }
    }
  }

  EVE_MAKE_CALLABLE(exp10_, exp10);


  namespace detail
  {
    // range_max
    template<unsigned_value T> constexpr auto range_max<tag::exp10_(T)>  =  sizeof(element_type_t<T>)*8-1;
    template<signed_integral_value T> constexpr auto range_max<tag::exp10_(T)>  =  sizeof(element_type_t<T>)*8-2;

    template<> inline constexpr auto range_max<tag::exp10_(float)>  =  0x1.330cf2p+5f;       //  38.38132095336914f;
    template<> inline constexpr auto range_max<tag::exp10_(double)> =  0x1.341aace35660fp+8; // 308.1042005620848;

    template<typename T> inline constexpr T range_max<tag::exp10_(pedantic_type, T)> = range_max<tag::exp10_(T)>;

    // range_min
    template<> inline constexpr auto range_min<tag::exp10_(float)>  = -0x1.2f704p+5f;  // -3.7929779e+01f;
    template<> inline constexpr auto range_min<tag::exp10_(double)> = -0x1.33a7146f72a42p+8;  // -3.076526555685888e+02;

    template<> inline constexpr auto range_min<tag::exp10_(pedantic_type, float)> =
      platform::supports_denormals ? -45.0f
      : range_min<tag::exp10_(float)>;

    template<> inline constexpr auto range_min<tag::exp10_(pedantic_type, double)> =
      platform::supports_denormals ? -323.0
      : range_min<tag::exp10_(double)>;

    template<> inline constexpr auto supports_pedantic<tag::exp10_> = true;

    template<typename T> inline constexpr T range_min<tag::exp10_(regular_type, T)> = range_min<tag::exp10_(T)>;
  }

}

#include <eve/module/math/function/generic/exp10.hpp>
