# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\arkmidnight_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\arkmidnight_autogen.dir\\ParseCache.txt"
  "arkmidnight_autogen"
  )
endif()
