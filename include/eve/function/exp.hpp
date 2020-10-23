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
  EVE_MAKE_CALLABLE(exp_, exp);

  namespace detail
  {
    template<typename T>
    inline constexpr auto range_min<tag::exp_(T)> =
    []()
    {
      if constexpr(std::same_as<T,float>) return -87.376259f;
      else                                return -708.39641853226420;
    }();

    template<typename T>
    inline constexpr auto range_min<tag::exp_(pedantic_type, T)> =
    []()
    {
      if constexpr(eve::platform::supports_denormals)
      {
        if constexpr(std::same_as<T,float>) return -103.972084f;
        else                                return -745.1332191019413358;
      }
      else
      {
        return range_min<tag::exp_(T)>;
      }
    }();

    template<typename T>
    inline constexpr auto range_max<tag::exp_(T)> =
    []()
    {
      if constexpr(std::same_as<T,float>) return 88.376259f;
      else                                return 709.43613930310391;
    }();

    template<>
    inline constexpr auto supports_pedantic<tag::exp_> = true;
  }
}

#include <eve/module/math/function/generic/exp.hpp>

