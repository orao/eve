//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/logical.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/function/bit_and.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE auto  binarize_(EVE_SUPPORTS(cpu_)
                           , logical<T> const &cond
                           ) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return  bit_and(one(eve::as<T>()),cond.bits());
    }
    else return  apply_over(binarize, cond);
  }

  template<real_value T, real_scalar_value U>
  EVE_FORCEINLINE auto binarize_(EVE_SUPPORTS(cpu_)
                           , logical<T> const &cond
                           , U const & val
                           ) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return  bit_and(T(val),cond.bits());
    }
    else return  apply_over(binarize, cond, val);
  }

  template<real_value T>
  EVE_FORCEINLINE auto binarize_(EVE_SUPPORTS(cpu_)
                           , logical<T> const &cond
                           , callable_allbits_ const &
                           ) noexcept
  {
    return cond.mask();
  }

  template<real_value T>
  EVE_FORCEINLINE auto binarize_(EVE_SUPPORTS(cpu_)
                           , logical<T> const &cond
                           , callable_mone_ const &
                           ) noexcept
  {
    if constexpr(integral_value<T>) return  cond.mask();
    else                            return  eve::binarize(cond,mone(eve::as<value_type_t<T>>()));
  }
}
