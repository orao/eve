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

namespace eve::detail
{
  //================================================================================================
  // Pattern based on MOVHL/MOVLH and partial zeroing
  //================================================================================================
  struct mov_match
  {
    template<typename In, typename Out, std::ptrdiff_t... I>
    static constexpr auto check(pattern_<I...>, as_<In>, as_<Out>)  noexcept
    {
      constexpr pattern_<I...> p{};

      return      sizeof(element_type_t<In>) == 4
            &&  (     p == pattern< 0, 1, 0, 1> // movlh
                  ||  p == pattern< 0, 1,-1,-1>
                  ||  p == pattern< 2, 3, 2, 3> // movhl
                  ||  p == pattern< 2, 3,-1,-1>
                  ||  p == pattern< 2, 3>
                );
    }
  };

  //================================================================================================
  // Pattern based on binary MOVHL/MOVLH
  //================================================================================================
  struct mov_binary_match
  {
    template<typename In, typename Out, std::ptrdiff_t... I>
    static constexpr auto check(pattern_<I...>, as_<In>, as_<Out>)  noexcept
    {
      constexpr pattern_<I...> p{};

      return      sizeof(element_type_t<In>) == 4
            &&  (     p == pattern< 0, 1, 4, 5> // movlh
                  ||  p == pattern< 4, 5, 0, 1>
                  ||  p == pattern< 2, 3, 6, 7> // movhl
                  ||  p == pattern< 6, 7, 2, 3>
                );
    }
  };

  template<typename Wide, typename Target, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(sse2_), mov_match const&
                                  , as_<Target> , Pattern const&, Wide const& v
                                  )
  {
    auto perm = [&]<typename W>(W r) -> W
    {
      constexpr Pattern p{};

            if constexpr(p == pattern<0,1, 0, 1>) return _mm_movelh_ps(r,r);
      else  if constexpr(p == pattern<0,1,-1,-1>) return _mm_movelh_ps(r,_mm_setzero_ps());
      else  if constexpr(p == pattern<2,3, 2, 3>) return _mm_movehl_ps(r,r);
      else  if constexpr(p == pattern<2,3>      ) return _mm_movehl_ps(r,r);
      else  if constexpr(p == pattern<2,3,-1,-1>) return _mm_movehl_ps(_mm_setzero_ps(),r);
    };

    return bit_cast( perm( bit_cast(v, as_<wide<float,cardinal_t<Wide>>>() )), as_<Target>() );
  }

  template<typename Wide, typename Target, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto do_shuffle ( EVE_SUPPORTS(sse2_), mov_binary_match const&
                                  , as_<Target> , Pattern const&
                                  , Wide const& v0, Wide const& v1
                                  )
  {
    auto perm = [&]<typename W>(W a, W b) -> W
    {
      constexpr Pattern p{};

            if constexpr(p == pattern<0, 1, 4, 5>) return _mm_movelh_ps(a,b);
      else  if constexpr(p == pattern<4, 5, 0, 1>) return _mm_movelh_ps(b,a);
      else  if constexpr(p == pattern<2, 3, 6, 7>) return _mm_movehl_ps(a,b);
      else  if constexpr(p == pattern<6, 7, 2, 3>) return _mm_movehl_ps(b,a);
    };

    return bit_cast ( perm( bit_cast(v0, as_<wide<float,cardinal_t<Wide>>>() )
                          , bit_cast(v1, as_<wide<float,cardinal_t<Wide>>>() )
                          )
                    , as_<Target>()
                    );
  }
}
