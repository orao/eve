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

#include <eve/traits/element_type.hpp>
#include <limits>

namespace eve
{
  // Concept to discriminate decorator wrapper
  template<typename T> concept semantic_wrappee = requires(T a)
  {
    typename T::semantic_type;
    typename T::callable_type;
  };

  namespace detail
  {
    // range-min extension point
    template<typename T> inline constexpr auto range_min =  std::numeric_limits<T>::lowest();

    template<typename Tag, typename T0, typename... T>
    inline constexpr auto range_min<Tag(T0,T...)> = range_min<T0>;

    template<typename Tag, typename X, typename T0, typename... T>
    inline constexpr auto range_min<callable_object<Tag,X>(T0,T...)>
                        = range_min<Tag(T0,T...)>;

    template<semantic_wrappee W, typename T0, typename... T>
    inline constexpr
    auto  range_min<W(T0,T...)>
        = range_min<typename W::callable_type(typename W::semantic_type,T0,T...)>;

    // range-max extension point
    template<typename T> inline constexpr auto range_max = std::numeric_limits<T>::max();

    template<typename Tag, typename T0, typename... T>
    inline constexpr auto range_max<Tag(T0,T...)> = range_max<T0>;

    template<typename Tag, typename X, typename T0, typename... T>
    inline constexpr auto range_max<callable_object<Tag,X>(T0,T...)>
                        = range_max<Tag(T0,T...)>;

    template<semantic_wrappee W, typename T0, typename... T>
    inline constexpr
    auto  range_max<W(T0,T...)>
        = range_max<typename W::callable_type(typename W::semantic_type,T0,T...)>;

    // numeric support extension point
    template<typename T> inline constexpr auto supports_numeric = false;

    template<typename Tag, typename X>
    inline constexpr
    auto supports_numeric<callable_object<Tag,X>> = supports_numeric<Tag>;

    template<semantic_wrappee W>
    inline constexpr
    auto  supports_numeric<W>
        = supports_numeric<typename W::callable_type(typename W::semantic_type)>;

    // pedantic support extension point
    template<typename T> inline constexpr auto supports_pedantic  = false;

    template<typename Tag, typename X>
    inline constexpr
    auto supports_pedantic<callable_object<Tag,X>> = supports_pedantic<Tag>;

    template<semantic_wrappee W>
    inline constexpr
    auto  supports_pedantic<W>
        = supports_pedantic<typename W::callable_type(typename W::semantic_type)>;

    // raw support extension point
    template<typename T> inline constexpr auto supports_raw = false;

    template<typename Tag, typename X>
    inline constexpr
    auto supports_raw<callable_object<Tag,X>> = supports_raw<Tag>;

    template<semantic_wrappee W>
    inline constexpr
    auto  supports_raw<W>
        = supports_raw<typename W::callable_type(typename W::semantic_type)>;

    // saturated support extension point
    template<typename T> inline constexpr auto supports_saturated = false;

    template<typename Tag, typename X>
    inline constexpr
    auto supports_saturated<callable_object<Tag,X>> = supports_saturated<Tag>;

    template<semantic_wrappee W>
    inline constexpr
    auto  supports_saturated<W>
        = supports_saturated<typename W::callable_type(typename W::semantic_type)>;
  }

  //------------------------------------------------------------------------------------------------
  // Properties of callables
  template<typename... T, typename Callable>
  constexpr auto range_min(Callable const&) noexcept
  {
    return detail::range_min<Callable(eve::element_type_t<T>...)>;
  }

  template<typename... T, typename Callable>
  constexpr auto range_max(Callable const&) noexcept
  {
    return detail::range_max<Callable(eve::element_type_t<T>...)>;
  }

  template<typename Callable>
  constexpr auto supports_numeric(Callable const&) noexcept
  {
    return detail::supports_numeric<Callable>;
  }

  template<typename Callable>
  constexpr auto supports_pedantic(Callable const&) noexcept
  {
    return detail::supports_pedantic<Callable>;
  }

  template<typename Callable>
  constexpr auto supports_raw(Callable const&) noexcept
  {
    return detail::supports_raw<Callable>;
  }

  template<typename Callable>
  constexpr auto supports_saturated(Callable const&) noexcept
  {
    return detail::supports_saturated<Callable>;
  }
}
