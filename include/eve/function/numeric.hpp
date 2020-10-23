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
  struct numeric_type;

  namespace detail
  {
    //================================================================================================
    // Internal raw wrapper as we need to be able to discriminate numeric-wrapped callable
    template<typename Callable>
    struct numeric_
    {
      using semantic_type = numeric_type;
      using callable_type = Callable;
      template<typename... Args> auto operator()(Args&&... args) const;
      Callable func;
    };
  }

  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct numeric_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  detail::numeric_{f};
    }
  };

  //================================================================================================
  // Function decorator - numeric mode
  inline constexpr numeric_type const numeric = {};

  //================================================================================================
  // Wrapper implementation
  namespace detail
  {
    template<typename Callable>
    template<typename... Args> auto numeric_<Callable>::operator()(Args&&... args) const
    {
      return func(numeric_type{}, std::forward<Args>(args)...);
    }
  }
}

