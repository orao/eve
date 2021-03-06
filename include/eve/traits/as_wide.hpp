//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/forward.hpp>
#include <eve/concept/rebindable.hpp>
#include <eve/detail/is_wide.hpp>
#include <utility>
#include <array>
#include <tuple>

namespace eve
{
  template<typename Type, typename Size = expected_cardinal_t<Type>>
  struct as_wide;

  template<typename Type, typename Size> requires( std::is_arithmetic_v<Type> )
  struct as_wide<Type,Size>
  {
    using type = eve::wide<Type,Size>;
  };

  template<typename T, typename Size>
  struct as_wide<eve::logical<T>,Size>
  {
    using type = eve::logical< typename as_wide<T,Size>::type >;
  };

  template<typename Type, typename N, typename Size>
  struct as_wide<eve::wide<Type,N>,Size>
  {
    using type = eve::wide<Type,Size>;
  };

  template<typename Type, typename N, typename Size>
  struct as_wide<eve::logical<eve::wide<Type,N>>,Size>
  {
    using type = eve::logical<eve::wide<Type,Size>>;
  };

  //================================================================================================
  // as_wide on type supporting structured_binding builds a new tuple of wide
  //================================================================================================
  template<typename T, typename Size> requires( rebindable<T> && !detail::is_wide<T>::value )
  struct as_wide<T,Size>
  {
    template<typename U,std::size_t N> struct aw
    {
      using type = typename eve::as_wide<std::tuple_element_t<N,U>,Size>::type;
    };

    template<typename Idx>      struct rebuild;
    template<std::size_t... N>  struct rebuild<std::index_sequence<N...>>
    {
      using type = std::tuple< typename aw<T,N>::type... >;
    };

    using size = std::tuple_size<T>;
    using type = typename rebuild<std::make_index_sequence<size::value>>::type;
  };

  //================================================================================================
  // Special case :std::pair gives std::pair
  //================================================================================================
  template<typename T, typename U, typename Size>
  requires( !detail::is_wide<std::pair<T,U>>::value )
  struct as_wide<std::pair<T,U>,Size>
  {
    using type = std::pair<typename as_wide<T,Size>::type, typename as_wide<U,Size>::type>;
  };

  //================================================================================================
  // Special case :std::array gives std::array
  //================================================================================================
  template<typename T, std::size_t N, typename Size>
  requires( !detail::is_wide<std::array<T,N>>::value )
  struct as_wide<std::array<T,N>,Size>
  {
    using type = std::array<typename as_wide<T,Size>::type, N>;
  };

  template<typename Type, typename Size = expected_cardinal_t<Type> >
  using as_wide_t = typename as_wide<Type, Size>::type;
}

