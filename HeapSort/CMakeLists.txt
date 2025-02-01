include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/public)
add_executable(hpsrt heap_sort.c)

target_link_libraries(hpsrt public)

set_target_properties(hpsrt PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
