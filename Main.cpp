
#include "ReservedOptions.hpp"
#include "src/CommandHandler.hpp"
#include "src/Option.hpp"
#include <iostream>


auto main(int argc, char** argv) -> int {
    /// Alias for quit command
    const Option exitOption{
            .id = ReservedOptions::QUIT_ID,
            .verboseName = "--exit",
            .quickName = "-e",
            .description = "Exits the program. The same as --quit / -q.",
            .function = [](std::vector<std::string> const& args) {
                std::cout << "This option also quit the program." << std::endl;
                exit(0);
            }};


    const Option manualOption{
            .id = 8,
            .verboseName = "--manual",
            .quickName = "-m",
            .description = "Gives you the manual of the program.",
            .function = [](std::vector<std::string> const& args) {
                std::cout << "This is a manual option." << std::endl;
            }};

    // Program arguments as a vector of strings.
    const auto args = std::vector<std::string>(argv, argv + argc);

    // CommandHandler
    CommandHandler commandHandler(args);
    commandHandler.add(manualOption);
    commandHandler.add(exitOption);

    commandHandler.execute();


    return 0;
}
