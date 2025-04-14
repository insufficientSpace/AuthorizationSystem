# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\autorizationSystem_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\autorizationSystem_autogen.dir\\ParseCache.txt"
  "autorizationSystem_autogen"
  )
endif()
