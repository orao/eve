//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/all.hpp>

namespace eve
{
  namespace tag { struct ldexp_; }

  namespace detail
  {
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_SUPPORTS(eve::tag::ldexp_), T const&, [[maybe_unused]]  U const& b)
    {
      if constexpr(std::is_floating_point_v<value_type_t<U>>)
        EVE_ASSERT(eve::all(is_flint(b)), "[eve::ldexp] argument 2 is floating but not a flint");
    }
  }

  EVE_MAKE_CALLABLE(ldexp_, ldexp);
}

#include <eve/module/real/core/function/regular/generic/ldexp.hpp>
