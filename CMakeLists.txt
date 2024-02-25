cmake_minimum_required(VERSION 3.10)
project(PomodoroTimer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SERVER_SOURCES
    Server_main.cpp
    Timer.cpp
    Server.cpp
    Message.cpp
    Config.cpp
)

set(CLIENT_SOURCES
    Client_main.cpp
    Client.cpp
    Message.cpp
    Config.cpp
)

set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

file(MAKE_DIRECTORY ${BIN_DIR})

add_executable(server ${SERVER_SOURCES})
add_executable(client ${CLIENT_SOURCES})

target_compile_options(server PRIVATE -Wall -Wextra -pedantic)
target_compile_options(client PRIVATE -Wall -Wextra -pedantic)

set_target_properties(server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
)

set_target_properties(client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
)

add_custom_target(build_all
    DEPENDS server client
)

add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove
        ${BIN_DIR}/server
        ${BIN_DIR}/client
)