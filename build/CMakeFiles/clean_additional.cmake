# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\appProfitAgent_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appProfitAgent_autogen.dir\\ParseCache.txt"
  "appProfitAgent_autogen"
  )
endif()
