//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rotr.hpp>
#include <eve/constant/allbits.hpp>
#include <bit>

TTS_CASE_TPL("Check eve::rotr return type", EVE_TYPE)
{
  using i_t = eve::as_integer_t<T, signed>;
  using u_t = eve::as_integer_t<T, unsigned>;

  TTS_EXPR_IS(eve::rotr(T(), T())   , T);
  TTS_EXPR_IS(eve::rotr(T(), i_t()) , T);
  TTS_EXPR_IS(eve::rotr(T(), u_t()) , T);
}

TTS_CASE_TPL("Check eve::rotr behavior", EVE_TYPE)
{
  using v_t   = eve::element_type_t<T>;
  using ui_t  = eve::as_integer_t<v_t, unsigned>;

  TTS_EQUAL(eve::rotr(T(0)              ,  7) , T(std::rotr(ui_t(0)             ,  7)) );
  TTS_EQUAL(eve::rotr(T(1)              ,  4) , T(std::rotr(ui_t(1)             ,  4)) );
  TTS_EQUAL(eve::rotr(T(3)              ,  2) , T(std::rotr(ui_t(3)             ,  2)) );
  TTS_EQUAL(eve::rotr(eve::allbits(eve::as<T>()) ,  1) , T(std::rotr(eve::allbits(eve::as<ui_t>()),  1)) );
  TTS_EQUAL(eve::rotr(T(0)              , -7) , T(std::rotr(ui_t(0)             , -7)) );
  TTS_EQUAL(eve::rotr(T(1)              , -4) , T(std::rotr(ui_t(1)             , -4)) );
  TTS_EQUAL(eve::rotr(T(3)              , -2) , T(std::rotr(ui_t(3)             , -2)) );

  TTS_EQUAL(eve::rotr(T(0)              , T(7)) , T(std::rotr(ui_t(0)             ,  7)) );
  TTS_EQUAL(eve::rotr(T(1)              , T(4)) , T(std::rotr(ui_t(1)             ,  4)) );
  TTS_EQUAL(eve::rotr(T(3)              , T(2)) , T(std::rotr(ui_t(3)             ,  2)) );
  TTS_EQUAL(eve::rotr(eve::allbits(eve::as<T>()) , T(1)) , T(std::rotr(eve::allbits(eve::as<ui_t>()),  1)) );
}
