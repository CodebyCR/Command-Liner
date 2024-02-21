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

    auto getFilteredArgs() -> std::vector<std::string> {
        std::vector<std::string> filteredArgs;
        // drop the first argument, which is the program name
        rawArgs.erase(rawArgs.begin());

        std::ranges::copy_if(rawArgs, std::back_inserter(filteredArgs), [](auto const& arg) {
            return !arg.starts_with('-');
        });

        return filteredArgs;
    }

    auto getRawCommands() -> std::vector<std::string> {
        std::vector<std::string> rawCommands;
        // drop the first argument, which is the program name
        rawArgs.erase(rawArgs.begin());

        std::ranges::copy_if(rawArgs, std::back_inserter(rawCommands), [](auto const& arg) {
            return arg.starts_with('-');
        });

        return rawCommands;
        }


    auto getTotalCommand() -> std::uint64_t {
        std::uint64_t totalCommand = 0;

        for(auto const& rawCommand: getRawCommands()) {
            for(auto const& cmd: commands) {
                if(rawCommand == cmd.verboseName || rawCommand == cmd.quickName) {
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
        auto filteredArgs = getFilteredArgs();
        auto totalCommand = getTotalCommand();

        for(auto const& cmd: commands) {
            if(totalCommand & cmd.id) {
                cmd.function(filteredArgs);
            }
        }
    }
};
