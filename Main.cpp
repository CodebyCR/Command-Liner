
#include "src/Command.hpp"
#include "src/CommandHandler.hpp"
#include <iostream>


auto main(int argc, char** argv) -> int {
    const Command exitCommand{
            .id = 0,
            .verboseName = "--exit",
            .quickName = "-e",
            .description = "Exits the program.",
            .function = [](std::vector<std::string> const& args) {
                std::cout << "This is an exit command." << std::endl;
            }};

    const Command helpCommand{
            .id = 2,
            .verboseName = "--help",
            .quickName = "-h",
            .description = "Gives you a helpful description about the command.",
            .function = [](std::vector<std::string> const& args) {
                std::cout << "This is a help command." << std::endl;
            }};

    const Command versionCommand{
            .id = 4,
            .verboseName = "--version",
            .quickName = "-v",
            .description = "Gives you the version of the program.",
            .function = [](std::vector<std::string> const& args) {
                std::cout << "This is a version command." << std::endl;
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
    commandHandler.add(helpCommand);
    commandHandler.add(versionCommand);
    commandHandler.add(manualCommand);
    commandHandler.add(exitCommand);

    commandHandler.execute();


    return 0;
}
