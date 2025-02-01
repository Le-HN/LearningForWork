include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/public)
add_executable(extsrt external_sort.c)

target_link_libraries(extsrt public)

set_target_properties(extsrt PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
