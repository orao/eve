//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_lez.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/saturated/convert.hpp>
#include <eve/function/saturated/div.hpp>
#include <eve/function/saturated/dec.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE T div_(EVE_SUPPORTS(cpu_), downward_type const &, T const &a, T const &b) noexcept
      requires has_native_abi_v<T>
  {
    using elt_t = element_type_t<T>;
    if constexpr( floating_real_value<T> )
    {
      return floor(div(a, b));
    }
    else if constexpr( integral_real_value<T> )
    {
      if constexpr( scalar_value<T> )
      {
        if constexpr( signed_value<T> )
        {
          if constexpr( std::is_same_v<elt_t, std::int64_t> )
          {
            if( !a )
              return zero(eve::as<T>());
            if( b )
            {
              auto q = saturated(div)(a, b);
              auto r = a - q * b;
              if( is_nez(r) && ((a ^ b) <= 0) )
                return saturated(dec)(q);
              else
                return q;
            }
            else
              return ((a > 0) ? valmax(eve::as<T>()) : valmin(eve::as<T>()));
          }
          else
          {
            if( b )
              return saturated(convert)(floor(static_cast<double>(a) / static_cast<double>(b)),
                                         as<T>());
            else
              return (a) ? ((a > 0) ? valmax(eve::as<T>()) : valmin(eve::as<T>())) : zero(eve::as<T>());
          }
        }
        else if constexpr( unsigned_value<T> )
        {
          if( b )
            return saturated(div)(a, b);
          else
            return bit_mask(a);
        }
      }
      else if constexpr( simd_value<T> )
      {
        if constexpr( signed_integral_value<T> )
        {
          if constexpr( std::is_same_v<elt_t, std::int64_t> )
          {
            auto bb = if_else(is_eqz(b), eve::one, b);
            auto q  = saturated(eve::div)(a, bb);
            auto r  = a - q * b;
            q       = saturated(dec[is_nez(r) && is_lez(bit_xor(a, b))])(q);
            auto z  = if_else(is_gtz(a), valmax(eve::as<T>()), valmin(eve::as<T>()));
            z       = if_else(is_eqz(a), eve::zero, z);
            return if_else(is_nez(b), q, z);
          }
          else
          {
            auto z = if_else(is_gtz(a), valmax(eve::as<T>()), valmin(eve::as<T>()));
            z      = if_else(is_eqz(a), eve::zero, z);
            auto q =
              saturated(convert)(floor(float64(a) / float64(b)), as<elt_t>());
            return if_else(is_nez(b), q, z);
          }
        }
        else if constexpr( unsigned_value<T> )
        {
          auto bb = if_else(is_eqz(b), eve::allbits, b);
          T    q  = saturated(div)(a, bb);
          return if_else(is_nez(b), q, bit_mask(a));
        }
      }
    }
  }
}
