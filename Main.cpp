
#include "src/Command.hpp"
#include "src/CommandHandler.hpp"
#include "ReservedCommands.hpp"
#include <iostream>


auto main(int argc, char** argv) -> int {

    /// Alias for quit command
    const Command exitCommand{
            .id = ReservedCommands::QUIT_ID,
            .verboseName = "--exit",
            .quickName = "-e",
            .description = "Exits the program. The same as --quit / -q.",
            .function = [](std::vector<std::string> const& args) {
                std::cout << "This command also quit the program." << std::endl;
                exit(0);
            }};


    const Command manualCommand{
            .id = 8,
            .verboseName = "--manual",
            .quickName = "-m",
            .description = "Gives you the manual of the program.",
            .function = [](std::vector<std::string> const& args) {
                std::cout << "This is a manual command." << std::endl;
            }};

    // Program arguments as a vector of strings.
    const auto args = std::vector<std::string>(argv, argv + argc);

    // CommandHandler
    CommandHandler commandHandler(args);
    commandHandler.add(manualCommand);
    commandHandler.add(exitCommand);

    commandHandler.execute();


    return 0;
}
