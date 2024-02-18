cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

project("CommandLiner" VERSION ${PROJECT_VERSION} LANGUAGES CXX)
message(NOTICE "${PROJECT_NAME}: ${PROJECT_VERSION}")

set(SUB_LIB_COUNT 1)

# Add Font library
set(COMMAND_LIBRARY "src" )
add_subdirectory(${COMMAND_LIBRARY})
if (COMMAND_LIBRARY)
    message(NOTICE " - [1/${SUB_LIB_COUNT}] ${COMMAND_LIBRARY} found")
else()
    message(FATAL_ERROR " - [1/${SUB_LIB_COUNT}] ${COMMAND_LIBRARY} not found")
endif()

add_executable(${PROJECT_NAME} "Main.cpp")


# Link the libraries
set_target_properties(${COMMAND_LIBRARY} PROPERTIES LINKER_LANGUAGE CXX)
include_directories(${COMMAND_LIBRARY})

# message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

# Create a library for find_package
install(TARGETS ${PROJECT_NAME}
        EXPORT ${COMMAND_LIBRARY}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

# Create a config file for find_package
install(TARGETS ${COMMAND_LIBRARY}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)
