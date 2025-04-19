include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/public)
add_executable(shmpdcr producer.c)
add_executable(shmcsmr consumer.c)

target_link_libraries(shmpdcr public)
target_link_libraries(shmcsmr public)

set_target_properties(shmpdcr PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set_target_properties(shmcsmr PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
