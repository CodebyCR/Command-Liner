<h1 align="center">Command Liner</h1>

<div align="center">
    <img height="28" src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="Logo" >
    <img height="28" src="https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white" alt="Logo">
    <img height="28" src="https://img.shields.io/github/license/CodeByCR/TimedAction?style=for-the-badge" alt="Logo">
    <h6><em>A handy header-only library that helps you to make your libraries to command-line applications.</em></h6>
</div>

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
                std::cout << "Here can I execute the function for my command\n"
                          << "with the arguments: "
                          << std::endl;

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
