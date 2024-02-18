//
// Created by Christoph Rohde on 02.02.24.
//

#pragma once


#include "Command.hpp"
#include <iostream>
#include <vector>


class CommandHandler {
private:
    std::vector<std::string> rawArgs;

    std::vector<Command> commands;

//    auto getFilteredArgs() -> std::vector<std::string> {
//        std::vector<std::string> filteredArgs;
//
//        if(rawArgs.size() == 1) {
//            return filteredArgs;
//        }
//
//        // drop the first argument, which is the program name
//        rawArgs.erase(rawArgs.begin());
//
//        std::ranges::copy_if(rawArgs, std::back_inserter(filteredArgs), [](auto const& arg) {
//            return !arg.starts_with("-");
//        });
//
//        return filteredArgs;
//    }

    auto getFilteredArgs() -> std::vector<std::string> {
        std::vector<std::string> filteredArgs;
        // drop the first argument, which is the program name
        rawArgs.erase(rawArgs.begin());
//        rawCommands.erase(rawCommands.begin());

        std::ranges::copy_if(rawArgs, std::back_inserter(filteredArgs), [](auto const& arg) {
            return arg != "cli" && !arg.starts_with("-");
        });

        return filteredArgs;
    }

    auto getTotalCommand() -> std::uint32_t {
        const auto filteredArgs = getFilteredArgs();
        std::uint32_t totalCommand = 0;

        for(auto const& arg: filteredArgs) {
            std::cout << "arg: " << arg << std::endl;
            for(auto const& cmd: commands) {
//                std::cout << arg << " " << cmd.verboseName << std::endl;
                if(arg == cmd.verboseName || arg == cmd.quickName) {
                    totalCommand = totalCommand + cmd.id;
                }
            }
        }

        return totalCommand;
    }

public:
    explicit CommandHandler(std::vector<std::string> const& args) : rawArgs(args) {}

    auto add(Command const& command) {
        commands.push_back(command);
    }

    auto execute() -> void {
        auto totalCommand = getTotalCommand();
        auto filteredArgs = getFilteredArgs();

        std::cout << "Total Commands: " << totalCommand << std::endl;
        std::cout << "Filtered Args: " << filteredArgs.size() << std::endl;

        for(auto const& cmd: commands) {
//            std::cout << totalCommand << " " << cmd.verboseName << std::endl;
            if(totalCommand & cmd.id) {
                std::cout << "Execute: " << cmd.verboseName << std::endl;
                cmd.function(filteredArgs);
            }
        }
    }
};
