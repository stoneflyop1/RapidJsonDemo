# CMakeList.txt : CMake project for RapidJsonDemo, include source and define
# project specific logic here.
#

# rapidjson 
include_directories("../rapidjson/include")
add_compile_definitions(RAPIDJSON_HAS_STDSTRING=1)

# Add source to this project's executable.
add_executable (RapidJsonDemo "main.cpp" "RapidJsonWriter.h" "Shapes.h" "RapidJsonUtils.h" "ShapeUtils.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RapidJsonDemo PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
