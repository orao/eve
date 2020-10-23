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

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>

namespace eve
{
  namespace detail
  {
    //================================================================================================
    // Internal raw wrapper as we need to be able to discriminate numeric-wrapped callable
    template<typename Callable>
    struct pedantic_
    {
      template<typename... Args> auto operator()(Args&&... args) const;
      Callable func;
    };
  }

  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct pedantic_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  detail::pedantic_{f};
    }
  };

  //================================================================================================
  // Function decorator - pedantic mode
  inline constexpr pedantic_type const pedantic = {};

  //================================================================================================
  // Wrapper implementation
  namespace detail
  {
    template<typename Callable>
    template<typename... Args> auto pedantic_<Callable>::operator()(Args&&... args) const
    {
      return func(pedantic_type{}, std::forward<Args>(args)...);
    }
  }
}

