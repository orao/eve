//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/traits/common_compatible.hpp>
#include <eve/function/convert.hpp>
#include <eve/concept/value.hpp>

namespace eve
{
  //================================================================================================
  // Function decorator - converting mode
  struct converting_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return [f] <value T0, value ...Ts>(T0 const& arg0, Ts const&... args)
      {
        using c_t = common_compatible_t<Ts...>;
        using eltc_t = element_type_t<c_t>;
        using elt_t =  element_type_t<T0>;
        if constexpr(std::same_as<elt_t, eltc_t>)
          return f(arg0, args...);
        else
          return f(arg0, convert(args, as_<elt_t>())...);
      };
    }
  };

  using converting_type = decorated<converting_()>;
  inline constexpr converting_type const converting = {};
}
