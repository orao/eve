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

#include <eve/detail/implementation.hpp>
#include <eve/function/countl_zero.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  template<unsigned_value T>
  EVE_FORCEINLINE constexpr T ffs_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept
  {
    using elt_t = element_type_t<T>;
    if constexpr(has_native_abi_v<T>)
    {
      auto z = T(a0&-a0);
      return T((sizeof(elt_t)*8-1)-countl_zero(z));
    }
    else return apply_over(ffs, a0);
  }

}
