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

namespace eve
{
  EVE_MAKE_CALLABLE(ifrexp_, ifrexp);
  namespace detail
  {
    template<> inline constexpr auto supports_pedantic<tag::ifrexp_> = true;
    template<> inline constexpr auto supports_raw<tag::ifrexp_> = true;
  }
}

#include <eve/module/core/function/generic/ifrexp.hpp>
