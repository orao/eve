//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_nltz.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct rempio2_; }

  namespace detail
  {

    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::rempio2_), [[maybe_unused]]  T const& x)
    {
      EVE_ASSERT(eve::all(is_nltz(x)), "[eve::rempio2] :  parameter must be positive or nan, found:" << x);
    }
 }

  EVE_MAKE_CALLABLE(rempio2_, rempio2);
}

#include <eve/module/real/math/function/regular/generic/rempio2.hpp>
