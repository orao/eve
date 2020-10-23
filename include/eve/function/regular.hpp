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
  struct regular_type;

  namespace detail
  {
    //================================================================================================
    // Internal regular wrapper as we need to be able to discriminate regular-wrapped callable
    template<typename Callable>
    struct regular_
    {
      using semantic_type = regular_type;
      using callable_type = Callable;
      template<typename... Args> auto operator()(Args&&... args) const
      {
        return func(std::forward<Args>(args)...);
      }
      Callable func;
    };
  }

  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct regular_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  detail::regular_<Function>{f};
    }
  };

  //================================================================================================
  // Function decorator - regular mode
  inline constexpr regular_type const regular = {};
}
