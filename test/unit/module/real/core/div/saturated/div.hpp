//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/saturated/div.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE_TPL("Check saturated(eve::div) return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::saturated(eve::div)(  T() ,   T()), T);
  TTS_EXPR_IS(eve::saturated(eve::div)(v_t() ,   T()), T);
  TTS_EXPR_IS(eve::saturated(eve::div)(  T() , v_t()), T);
}

TTS_CASE_TPL("Check saturated(eve::div) behavior", EVE_TYPE)
{
  using eve::saturated;
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::integral_value<T>)
  {
    auto tvmax  = eve::valmax(eve::as<T>());
    auto vmax   = eve::valmax(eve::as<v_t>());

    if constexpr(eve::signed_value<T>)
    {
      auto vmin   = eve::valmin(eve::as<v_t>());
      auto tvmin  = eve::valmin(eve::as<T>());

      TTS_EQUAL(saturated(eve::div)(tvmax  , T(-1) ), tvmin+(T(1)) );
      TTS_EQUAL(saturated(eve::div)(tvmin  , T(-1) ), tvmax        );
      TTS_EQUAL(saturated(eve::div)(T(-1)  , T( 0) ), tvmin        );
      TTS_EQUAL(saturated(eve::div)(T(-2)  , T( 0) ), tvmin        );
      TTS_EQUAL(saturated(eve::div)(tvmin  , T( 0) ), tvmin        );
      TTS_EQUAL(saturated(eve::div)(T(1)   , T( 0) ), tvmax        );
      TTS_EQUAL(saturated(eve::div)(T(2)   , T( 0) ), tvmax        );
      TTS_EQUAL(saturated(eve::div)(tvmax  , T( 0) ), tvmax        );

      TTS_EQUAL(saturated(eve::div)(tvmax  , v_t(-1) ), tvmin+(T(1)) );
      TTS_EQUAL(saturated(eve::div)(tvmin  , v_t(-1) ), tvmax        );
      TTS_EQUAL(saturated(eve::div)(T(-1)  , v_t( 0) ), tvmin        );
      TTS_EQUAL(saturated(eve::div)(T(-2)  , v_t( 0) ), tvmin        );
      TTS_EQUAL(saturated(eve::div)(tvmin  , v_t( 0) ), tvmin        );
      TTS_EQUAL(saturated(eve::div)(T(1)   , v_t( 0) ), tvmax        );
      TTS_EQUAL(saturated(eve::div)(T(2)   , v_t( 0) ), tvmax        );
      TTS_EQUAL(saturated(eve::div)(tvmax  , v_t( 0) ), tvmax        );

      TTS_EQUAL(saturated(eve::div)(vmax   , T(-1)), tvmin+(T(1)));
      TTS_EQUAL(saturated(eve::div)(vmin   , T(-1)), tvmax       );
      TTS_EQUAL(saturated(eve::div)(v_t(-1), T( 0)), tvmin       );
      TTS_EQUAL(saturated(eve::div)(v_t(-2), T( 0)), tvmin       );
      TTS_EQUAL(saturated(eve::div)(vmin   , T( 0)), tvmin       );
      TTS_EQUAL(saturated(eve::div)(v_t(1) , T( 0)), tvmax       );
      TTS_EQUAL(saturated(eve::div)(v_t(2) , T( 0)), tvmax       );
      TTS_EQUAL(saturated(eve::div)(vmax   , T( 0)), tvmax       );
     }
    else
    {
      TTS_EQUAL(saturated(eve::div)(tvmax, T(1)), tvmax);
      TTS_EQUAL(saturated(eve::div)(T(1) , T(0)), tvmax);
      TTS_EQUAL(saturated(eve::div)(T(2) , T(0)), tvmax);
      TTS_EQUAL(saturated(eve::div)(tvmax, T(0)), tvmax);

      TTS_EQUAL(saturated(eve::div)(vmax   , T(1)), tvmax);
      TTS_EQUAL(saturated(eve::div)(v_t(1) , T(0)), tvmax);
      TTS_EQUAL(saturated(eve::div)(v_t(2) , T(0)), tvmax);
      TTS_EQUAL(saturated(eve::div)(vmax   , T(0)), tvmax);

      TTS_EQUAL(saturated(eve::div)(tvmax, v_t(1)), tvmax);
      TTS_EQUAL(saturated(eve::div)(T(1) , v_t(0)), tvmax);
      TTS_EQUAL(saturated(eve::div)(T(2) , v_t(0)), tvmax);
      TTS_EQUAL(saturated(eve::div)(tvmax, v_t(0)), tvmax);
    }
  }
  else
  {
    TTS_EQUAL(saturated(eve::div)(T( 0) , T(1)), T(0  ) );
    TTS_EQUAL(saturated(eve::div)(T( 1) , T(1)), T(1  ) );
    TTS_EQUAL(saturated(eve::div)(T(12) , T(4)), T(3  ) );
    TTS_EQUAL(saturated(eve::div)(T( 1) , T(2)), T(0.5) );

    TTS_EQUAL(saturated(eve::div)(v_t( 0) , T(1)), T(0  ) );
    TTS_EQUAL(saturated(eve::div)(v_t( 1) , T(1)), T(1  ) );
    TTS_EQUAL(saturated(eve::div)(v_t(12) , T(4)), T(3  ) );
    TTS_EQUAL(saturated(eve::div)(v_t( 1) , T(2)), T(0.5) );

    TTS_EQUAL(saturated(eve::div)(T( 0) , v_t(1)), T(0  ) );
    TTS_EQUAL(saturated(eve::div)(T( 1) , v_t(1)), T(1  ) );
    TTS_EQUAL(saturated(eve::div)(T(12) , v_t(4)), T(3  ) );
    TTS_EQUAL(saturated(eve::div)(T( 1) , v_t(2)), T(0.5) );
  }
}
