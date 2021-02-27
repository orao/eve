//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/memory/aligned_ptr.hpp>
#include <eve/function/store.hpp>
#include <eve/function/replace.hpp>
#include <eve/wide.hpp>

#include <array>
#include <numeric>

TTS_CASE_TPL("Check store behavior to unaligned arithmetic pointer", EVE_TYPE)
{
  std::array<EVE_VALUE, 3 * EVE_CARDINAL> ref;
  T value([](auto i, auto) { return 1 + i * 3; });

  for(int i = 0; i < EVE_CARDINAL; ++i)
  {
    ref[ i                  ] =  1 + i * 3;
    ref[ i + EVE_CARDINAL   ] =  1 + i * 3;
    ref[ i + 2*EVE_CARDINAL ] =  1 + i * 3;
  }

  std::array<EVE_VALUE, 3 * EVE_CARDINAL> target;

  eve::store(value, &target[ 0                ]);
  eve::store(value, &target[ EVE_CARDINAL     ]);
  eve::store(value, &target[ 2 * EVE_CARDINAL ]);

  TTS_ALL_EQUAL(target, ref);
}

TTS_CASE_TPL("Check store behavior to aligned arithmetic pointer", EVE_TYPE)
{
  constexpr auto algt = eve::alignment_v<T>;

  std::array<EVE_VALUE, 3 * EVE_CARDINAL> ref;
  T value([](auto i, auto) { return 1 + i * 3; });

  for(int i = 0; i < EVE_CARDINAL; ++i)
  {
    ref[ i                  ] =  1 + i * 3;
    ref[ i + EVE_CARDINAL   ] =  1 + i * 3;
    ref[ i + 2*EVE_CARDINAL ] =  1 + i * 3;
  }

  alignas(algt) std::array<EVE_VALUE, 3 * EVE_CARDINAL> target;

  eve::store(value, eve::as_aligned<algt>(&target[ 0                ]) );
  eve::store(value, eve::as_aligned<algt>(&target[ EVE_CARDINAL     ]) );
  eve::store(value, eve::as_aligned<algt>(&target[ 2 * EVE_CARDINAL ]) );

  TTS_ALL_EQUAL(target, ref);
}

TTS_CASE_TPL("store for different alignment", EVE_TYPE )
{
  using e_t = EVE_VALUE;
  std::array<e_t, 256> data;

  const T what{[](int i, int) { return i; }};
  const T zeroes{0};

  for (e_t* f =  data.begin();
            f != data.end() - EVE_CARDINAL + 1;
          ++f)
  {
    auto test = [&]<std::ptrdiff_t A>(eve::fixed<A>) {
      if (!eve::is_aligned<A>(f)) return;
      if constexpr (A >= T::static_alignment)
      {
        eve::aligned_ptr<e_t, static_cast<std::size_t>(A)> ptr{f};
        eve::store(what, ptr);
        TTS_EQUAL(T{f}, what);
        eve::store(zeroes, ptr);
        TTS_EQUAL(T{f}, zeroes);
        eve::store[eve::ignore_none](what, ptr);
        TTS_EQUAL(T{f}, what);
      }
    };

    test(eve::lane<128>);
    test(eve::lane<64>);
    test(eve::lane<32>);
    test(eve::lane<16>);
    test(eve::lane<8>);
    test(eve::lane<4>);
  }
}

TTS_CASE_TPL("store[ignore]", EVE_TYPE )
{
  using e_t = EVE_VALUE;

  const T what{[](int i, int) { return i; }};

  // ignore_all should not write anything
  {
    e_t garbage;
    eve::store[eve::ignore_all](what, &garbage + 5);
  }

  // write to one element (ASAN test).
  {
    e_t data;
    data = 17;
    eve::store[eve::ignore_first(T::static_size - 1)](what, &data - T::static_size + 1);
    TTS_EQUAL(data, what.back());

    eve::store[eve::ignore_last(T::static_size - 1)](what, &data);
    TTS_EQUAL(data, what.front());

    eve::store[eve::ignore_extrema_(0, T::static_size - 1)](what, &data);
    TTS_EQUAL(data, what.front());
  }

  // ignore doesn't write garbarge values
  {
    std::array<e_t, 256> data;
    const T filler{17};

    auto run_one_case = [&](auto ptr, auto ignore)
    {
      eve::store(filler, ptr);
      eve::store[ignore](what, ptr);
      T actual(ptr);
      T expected = eve::replace_ignored(what, ignore, filler);
      TTS_EQUAL(actual, expected);
    };

    auto run_all_ignores = [&](auto ptr)
    {
      for (int i = 0; i != T::static_size + 1; ++i)
      {
        run_one_case(ptr, eve::ignore_first(i));
        run_one_case(ptr, eve::ignore_last(i));

        for (int j = T::static_size - i; j != -1; --j)
        {
          run_one_case(ptr, eve::ignore_extrema_(i, j));
        }
      }
    };

    for (e_t* f = data.begin(); f != data.end() - T::static_size; ++f)
    {
      run_all_ignores(f);

      static constexpr std::ptrdiff_t alignment = sizeof(e_t) * T::static_size;

      if (!eve::is_aligned<alignment>(f)) continue;

      run_all_ignores(eve::aligned_ptr<e_t, alignment>(f));
    }
  }
}
