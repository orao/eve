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
  struct saturated_type;

  namespace detail
  {
    //================================================================================================
    // Internal raw wrapper as we need to be able to discriminate saturated-wrapped callable
    template<typename Callable>
    struct saturated_
    {
      using semantic_type = saturated_type;
      using callable_type = Callable;
      template<typename... Args> auto operator()(Args&&... args) const;
      Callable func;
    };
  }

  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct saturated_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  detail::saturated_{f};
    }
  };

  //================================================================================================
  // Function decorator - saturated mode
  inline constexpr saturated_type const saturated = {};

  //================================================================================================
  // Wrapper implementation
  namespace detail
  {
    template<typename Callable>
    template<typename... Args> auto saturated_<Callable>::operator()(Args&&... args) const
    {
      return func(saturated_type{}, std::forward<Args>(args)...);
    }
  }
}

