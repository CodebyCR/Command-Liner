
set(COMMAND_SOURCES
        "Command.hpp"
        "CommandHandler.hpp"
)

add_library(${COMMAND_LIBRARY} INTERFACE ${COMMAND_SOURCES} )

target_include_directories( ${COMMAND_LIBRARY}
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
