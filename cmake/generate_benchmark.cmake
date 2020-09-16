##==================================================================================================
##  EVE - Expressive Vector Engine
##
##  Copyright 2019 Joel FALCOU
##  Copyright 2019 Jean-Thierry LAPRESTE
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

include(add_parent_target)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set( _BenchOptions -std=c++20 -Wall)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set( _BenchOptions -std=c++20 -Wall)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set( _BenchOptions /std:c++latest -W3 -EHsc)
endif()

##==================================================================================================
## Setup a bench with many option
##==================================================================================================
function(generate_bench root rootpath dep file)
  string(REPLACE ".cpp" ".bench" base ${file})
  string(REPLACE "/"    "." base ${base})
  string(REPLACE "\\"   "." base ${base})

  if( NOT root STREQUAL "")
    set(bench "${root}.${base}")
  else()
    set(bench "${base}")
  endif()

  add_executable( ${bench}  "${rootpath}${file}")

  if( ${ARGC} EQUAL 5)
    target_compile_definitions( ${bench} PUBLIC ${ARGV4})
  endif()

  target_compile_options  ( ${bench} PUBLIC ${_BenchOptions} )

  set_property( TARGET ${bench}
                PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bench"
              )


    add_test( NAME ${bench}
              WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/bench"
              COMMAND $<TARGET_FILE:${bench}>
            )

  set_target_properties ( ${bench} PROPERTIES
                          EXCLUDE_FROM_DEFAULT_BUILD TRUE
                          EXCLUDE_FROM_ALL TRUE
                          ${MAKE_UNIT_TARGET_PROPERTIES}
                        )

  target_include_directories( ${bench}
                              PRIVATE
                                ${PROJECT_SOURCE_DIR}/include
                                ${PROJECT_SOURCE_DIR}/benchmarks
                                ${Boost_INCLUDE_DIRS}
                            )

  target_link_libraries(${bench})

  add_dependencies(bench ${bench})

  if( NOT dep STREQUAL "")
    add_dependencies(${dep} ${bench})
  endif()

  add_parent_target(${bench})
endfunction()