#include <eve/function/narrow.hpp>
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
  int16_t  si16 = 300;
  std::cout << "---- simd" << '\n'
            << "<- i8                                     = " << i8 << '\n'
            << "<- i16                                    = " << i16<< '\n'
            << "-> narrow(add)(i8, i16, i16)              = " << eve::narrow(eve::add)(i8, i16, i16) << '\n'
            << "-> narrow(add)(i8, i8, i8)                = " << eve::narrow(eve::add)(i8, i8, i8) << '\n'
            << "-> add(i8, i8, i8)                        = " << eve::add(i8, i8, i8) << '\n'
            << "-> narrow(add)(i8, si16, si16)            = " << eve::narrow(eve::add)(i8, si16, si16) << '\n'
            << "-> narrow(add)(i8, si16,  i16)            = " << eve::narrow(eve::add)(i8, si16,  i16) << '\n'
            << "-> add(i8, i16, si16)                     = " << eve::add(i8, i8, si8) << '\n'
            << "-> narrow(saturated(add))(i8, i16, i16)   = " << eve::narrow(eve::saturated(eve::add))(i8, i16, i16) << '\n'
            << "-> narrow(saturated(add)(i8, i8, i8)      = " << eve::narrow(eve::saturated(eve::add))(i8, i8, i8) << '\n';

  return 0;
}
