# Command-Liner

###### _A handy header-only library that helps you to make your libraries to command-line applications._

## Example usage

```cpp
#include "src/Command.hpp"
#include "src/CommandHandler.hpp"
#include <iostream>

auto main(int argc, char* argv[]) -> int {
    const Command myCommand{
            .id = 0,
            .verboseName = "--myCommand",
            .quickName = "-m",
            .description = "The description of my command.",
            .function = [](std::vector<std::string> const& args) {
                const auto text = "Here can I execute the function for my command\n";
                const auto text2 = "with the arguments: ";
                std::cout << text << text2  << std::endl;
                for (auto const& arg : args) {
                    std::cout << arg << std::endl;
                }
            }};

    // Program arguments as a vector of strings.
    const auto args = std::vector<std::string>(argv, argv + argc);

    // CommandHandler
    CommandHandler commandHandler(args);
    commandHandler.add(myCommand);
    commandHandler.execute();

    return 0;
}
```
