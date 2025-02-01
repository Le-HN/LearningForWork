include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/public)
add_executable(multrd multi_thread.c)

target_link_libraries(multrd public)

set_target_properties(multrd PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
