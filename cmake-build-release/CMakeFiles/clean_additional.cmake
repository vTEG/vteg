# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles/VTEg_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/VTEg_autogen.dir/ParseCache.txt"
  "CMakeFiles/breeze_themes_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/breeze_themes_autogen.dir/ParseCache.txt"
  "VTEg_autogen"
  "breeze_themes_autogen"
  )
endif()
