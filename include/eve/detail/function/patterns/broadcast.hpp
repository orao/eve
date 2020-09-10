//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/patterns.hpp>

#include <cstddef>

namespace eve::detail
{
  // Match any pattern of the form [k k ... k k]
  struct broadcast_match
  {
    template<typename Wide, std::ptrdiff_t I0, std::ptrdiff_t... I>
    static constexpr auto check(pattern_<I0,I...> const&, as_<Wide> const&)  noexcept
    {
      return ((I==I0) && ...);
    }
  };

  template<typename Target, typename Wide, std::ptrdiff_t I0, std::ptrdiff_t... I>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(cpu_), broadcast_match const&
                                  , as_<Target> , pattern_<I0,I...> const&
                                  , Wide const& v
                                  )
  {
    return Target(v[I0]);
  }
}