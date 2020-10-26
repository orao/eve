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

#include <eve/concept/value.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_finite.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/signnz.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sub.hpp>
#include <type_traits>
#include <eve/platform.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T expx2m_(EVE_SUPPORTS(cpu_), T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr(eve::platform::supports_invalids && scalar_value<T>)
      {
        if (is_nan(a0)) return a0;
      }
      T x =  abs(a0);
      auto gtmxlg =  x > eve::range_max<T>(eve::expx2m);
      x =  -x;
      if constexpr(scalar_value<T>)
      {
        if (gtmxlg) return zero(as<T>());
      }
      x =  -x;
      const T Expx2c1 = Ieee_constant<T, 0x42000000U, 0x4060000000000000ull>();
      const T Expx2c2 = Ieee_constant<T, 0x3d000000U, 0x3f80000000000000ull>();
      // Represent x as an exact multiple of 1/32 plus a residual.
      T m = Expx2c1*eve::floor(fma(Expx2c2, x, eve::half(as<T>())));
      T f =  sub[is_finite(x)](x, m);
      // x**2 = m**2 + 2mf + f**2
      T u = -eve::sqr(m);
      T u1 = -fma(m+m,f,sqr(f));
      // u is exact, u1 is small.
      T r = eve::if_else(gtmxlg, zero, eve::exp(u)*eve::exp(u1));
      if constexpr(eve::platform::supports_invalids)
        r =  eve::if_else(is_nan(a0), eve::allbits, r);
      return r;
    }
    else
      return apply_over(expx2m, a0);
  }

}
