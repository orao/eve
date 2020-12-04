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
#include <eve/function/abs.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/pedantic/ldexp.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/min.hpp>
#include <eve/function/maxmag.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/maxexponentm1.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_value T, floating_value U>
  EVE_FORCEINLINE  auto hypot_(EVE_SUPPORTS(cpu_)
                            , pedantic_type const &
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(pedantic(hypot), a, b);
  }

  template<floating_value T>
  EVE_FORCEINLINE auto hypot_( EVE_SUPPORTS(cpu_)
                             , pedantic_type const &
                             , T const &a
                             , T const &b
                             ) noexcept
  requires has_native_abi_v<T>
  {
    using elt_t =  element_type_t<T>;
    if constexpr(eve::platform::supports_invalids && scalar_value<T>)
      if (is_infinite(a) || is_infinite(b)) return inf(eve::as(a));
    if constexpr(std::is_same_v<elt_t, float>)
    {
      auto res = float32(hypot(float64(a), float64(b)));
      if constexpr(eve::platform::supports_invalids && simd_value<T>)
        return if_else(is_infinite(a) || is_infinite(b), inf(eve::as<T>()), res);
      else return res;
    }
    else
    {
      if constexpr(eve::platform::supports_invalids && scalar_value<T>) if (is_infinite(a) || is_infinite(b)) return inf(eve::as(a));
      auto e =  exponent(eve::maxmag(a, b));
      e = eve::min(eve::max(e,minexponent(eve::as<T>())),maxexponentm1(eve::as<T>()));
      auto tmp = pedantic(ldexp)(a, -e);
      auto res =  pedantic(ldexp)(sqrt(fma(tmp, tmp, sqr(pedantic(ldexp)(b, -e)))), e);
      if constexpr(eve::platform::supports_invalids && simd_value<T>)
        return if_else(is_infinite(a) || is_infinite(b), inf(eve::as<T>()), res);
      else return res;
    }
  }

  template<floating_value T, floating_value U, floating_value V>
  EVE_FORCEINLINE  auto hypot_(EVE_SUPPORTS(cpu_)
                              , pedantic_type const &
                              , T const &a
                              , U const &b
                              , V const &c) noexcept
  requires compatible_values<T, U> &&  compatible_values<T, V>
  {
    return arithmetic_call(pedantic(hypot), a, b, c);
  }

  template<floating_value T>
  EVE_FORCEINLINE auto hypot_( EVE_SUPPORTS(cpu_)
                             , pedantic_type const &
                             , T const &a
                             , T const &b
                             , T const &c
                             ) noexcept
  requires has_native_abi_v<T>
  {
    if constexpr(scalar_value<T>)
      if (is_infinite(a)|| is_infinite(b)|| is_infinite(c))  return inf(eve::as(a));
    if constexpr(std::is_same_v<value_type_t<T>, float>)
    {
      return float32(hypot(float64(a), float64(b), float64(c)));
    }
    else
    {
      auto e =  exponent(eve::maxmag(eve::maxmag(a, b), c));
      e = eve::min(eve::max(e,minexponent(eve::as<T>())),maxexponentm1(eve::as<T>()));
      auto tmpr = pedantic(ldexp)(a, -e);
      auto tmpi = pedantic(ldexp)(b, -e);
      auto tmpj = pedantic(ldexp)(c, -e);
      T res =  pedantic(ldexp)(eve::sqrt(fma(tmpr, tmpr, fma(tmpi, tmpi, sqr(tmpj)))), e);
      if constexpr(eve::platform::supports_invalids)
        return if_else(is_infinite(a) || is_infinite(b) || is_infinite(c), inf(eve::as<T>()), res);
      else  return res;
    }
  }
}