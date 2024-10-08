<h1 align="center">Command Liner</h1>

<div align="center">
    <img height="28" src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="Logo" >
    <img height="28" src="https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white" alt="Logo">
    <img height="28" src="https://img.shields.io/github/license/CodeByCR/TimedAction?style=for-the-badge" alt="Logo">
    <h4><em>A handy header-only library that helps you to make your libraries to command-line applications.</em></h4>
</div>

## Example usage

```cpp
#include "src/Option.hpp"
#include "src/CommandHandler.hpp"
#include <iostream>

auto getArgsString(std::vector<std::string> const& args) -> std::string {
    std::string argsString;

    for (auto const& arg : args) {
        argsString += arg + " ";
    }

    return argsString;
}

auto main(int argc, char* argv[]) -> int {
    const Option myOption{
            .id = 0,
            .verboseName = "--myCommand",
            .quickName = "-m",
            .description = "The description of my command.",
            .function = [](std::vector<std::string> const& args) {
                std::cout << "Here can I execute the function for my command\n"
                          << "with the arguments: "
                          << std::endl;

                return getArgsString(args);
            }};

    // Program arguments as a vector of strings.
    const auto args = std::vector<std::string>(argv, argv + argc);

    // CommandHandler
    CommandHandler commandHandler(args);
    commandHandler.add(myOption);
    commandHandler.execute();

    return 0;
}
```

## Pre defined Options

The following Options are defined by default.

| Option  | Name (Verbose \| Quick) |             Required Arguments              |
|:-------:|:------------------------|:-------------------------------------------:|
|  Quit   | `--quit`, `-q`          |                      —                      |
| Version | `--version`, `-v`       |                      —                      |
| Verbose | `--verbose`, `-V`       |                                             |
|  Help   | `--help`, `-h`          | Used the description off all given commands |
|         |                         |                                             |
|         |                         |                                             |
|         |                         |                                             |
|         |                         |                                             |

## Multi & combined option execution

All options there are defined as Commands and you use in a console command,
will be executed in order or together if there combined action defined.

## Up to 56 self defined Commands

Inside all commands toggle a bit of an unsigned integer with 64 bits (8 byte),
the last byte is reserved for pre-defined commands.
So you can define up to 56 Commands and for all of these combined actions if you want.
The list of arguments is untouched of any restrictions.

## Alias Commands

You can define alias command for an existing one to improve the user experience of your CLI Tool.

## Command Line Syntax

The syntax of the command line is as follows:

```bash
$ ./myProgram [options] [arguments]
```
