##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
include(test)

add_subdirectory(doc)
# add_subdirectory(exhaustive)

if( EVE_BUILD_RANDOM )
  add_subdirectory(random)
endif()

add_subdirectory(unit)
