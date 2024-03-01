<h1 align="center">Command Liner</h1>

<div align="center">
    <img height="28" src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="Logo" >
    <img height="28" src="https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white" alt="Logo">
    <img height="28" src="https://img.shields.io/github/license/CodeByCR/TimedAction?style=for-the-badge" alt="Logo">
    <h4><em>A handy header-only library that helps you to make your libraries to command-line applications.</em></h4>
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

## Pre defined commands

The following commands are defined by default.

| Command | Option            |             Requiered Arguments             |
| :-----: | :---------------- | :-----------------------------------------: |
|  Quit   | `--quit`, `-q`    |                      —                      |
| Version | `--version`, `-v` |                      —                      |
| Verbose | `--verbose`, `-V` |                                             |
|  Help   | `--help`, `-h`    | Used the description off all given commands |
|         |                   |                                             |
|         |                   |                                             |
|         |                   |                                             |
|         |                   |                                             |

## Multi & combind option execution

All options there are defined as Commands and you use in a consol command,
will be exectuted in order or together if there combinded action defined.

## Up to 56 self defined Commands

Inside all commands toggle a bit of an unsigned integer with 64 bits (8 byte),
the last byte is reserved for pre defined commands.
So you can define up to 56 Commands and for all of these combinded actions if you want.
The list of arguments is untouched of any restrictions.

## Alias Commands

You can define alias command for an existing one to improve the user experience of your CLI Tool.
