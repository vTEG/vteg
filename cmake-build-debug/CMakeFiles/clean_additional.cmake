# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\VTEg_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\VTEg_autogen.dir\\ParseCache.txt"
  "VTEg_autogen"
  )
endif()
