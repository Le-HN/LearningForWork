include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/public)
add_executable(sktsrv socket_com_server.c)
add_executable(sktclt socket_com_client.c)

target_link_libraries(sktsrv public)
target_link_libraries(sktclt public)

set_target_properties(sktsrv sktclt PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
