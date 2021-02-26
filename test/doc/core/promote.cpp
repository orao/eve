#include <eve/function/promote.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/saturated/add.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_i8 = eve::wide<std::int8_t, eve::fixed<4>>;
using wide_i16 = eve::wide<std::int16_t, eve::fixed<4>>;


int main()
{

  wide_i8  i8 = {1, 120, 54,  68};     // elements are int8_t
  wide_i16 i16= {1, 120, 54,  32760};  // elements are int16_t
  int8_t   si8 = 120;
  std::cout << "---- simd" << '\n'
            << "<- i8                                     = " << i8 << '\n'
            << "<- i16                                    = " << i16<< '\n'
            << "-> promote(add)(i16, i8, i8)              = " << eve::promote(eve::add)(i16, i8, i8) << '\n'
            << "-> promote(add)(i8, i8, i8)               = " << eve::promote(eve::add)(i8, i8, i8) << '\n'
            << "-> add(i8, i8, i8)                        = " << eve::add(i8, i8, i8) << '\n'
            << "-> promote(add)(i16, si8, si8)            = " << eve::promote(eve::add)(i16, si8, si8) << '\n'
            << "-> promote(add)(i16, si8,  i8)            = " << eve::promote(eve::add)(i16, si8,  i8) << '\n'
            << "-> add(i8, i8, si8)                       = " << eve::add(i8, i8, si8) << '\n'
            << "-> promote(saturated(add))(i16, i8, i8)   = " << eve::promote(eve::saturated(eve::add))(i16, i8, i8) << '\n'
            << "-> promote(saturated((add))(i8, i8, i8)    = " << eve::promote(eve::saturated(eve::add))(i8, i8, i8) << '\n';

  return 0;
}
