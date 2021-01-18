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

#include <eve/function/acos.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/sqr.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T acos_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T const &x) noexcept
  {
    return -rsqrt(oneminus(sqr(x)));
  }
}