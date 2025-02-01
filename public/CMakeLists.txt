include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(public SHARED public.c)

set_target_properties(public PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})
