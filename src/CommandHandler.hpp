//
// Created by Christoph Rohde on 02.02.24.
//

#pragma once


#include "Command.hpp"
#include "ReservedCommands.hpp"
#include <iostream>
#include <vector>


class CommandHandler {
private:
    std::vector<std::string> rawArgs;
    std::uint64_t totalCommand = {0};
    std::vector<Command> commands;
    bool isVerbose = false;


    auto getFilteredArgs() -> std::vector<std::string> {
        std::vector<std::string> filteredArgs;
        // drop the first argument, which is the program name
        rawArgs.erase(rawArgs.begin());

        std::ranges::copy_if(rawArgs, std::back_inserter(filteredArgs), [](auto const& arg) {
            return !arg.starts_with('-');
        });

        return filteredArgs;
    }

    auto executeInOrder() -> void {
        auto filteredArgs = getFilteredArgs();
        for(auto const& cmd: commands) {
            if(cmd.id & totalCommand) {
                cmd.function(filteredArgs);
            }
        }
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


    auto getTotalCommand() {
        for(auto const& rawCommand: getRawCommands()) {
            for(auto const& cmd: commands) {
                if(rawCommand == cmd.verboseName || rawCommand == cmd.quickName) {
                    this->totalCommand = this->totalCommand + cmd.id;
                }
            }
        }
    }

    auto showHelp([[maybe_unused]] std::vector<std::string> const& args) {

        // sort commands by cmd.quickName case-insensitive
        std::sort(commands.begin(), commands.end(), [](auto const& a, auto const& b) {
            return std::lexicographical_compare(a.quickName.begin(), a.quickName.end(), b.quickName.begin(), b.quickName.end(), [](char a, char b) {
                return std::tolower(a) < std::tolower(b);
            });
        });

        if(totalCommand != ReservedCommands::HELP_ID) {
            /// Remove all commands that are not in the totalCommand
            commands.erase(std::remove_if(commands.begin(), commands.end(), [this](auto const& cmd) {
                return !(cmd.id & this->totalCommand);
            }), commands.end());
        }


        const auto largestVerboseName = std::ranges::max_element(commands, {}, [](auto const& cmd) {
        return cmd.verboseName.size();
        });

        const std::string verboseName = "Verbose Name";
        const auto largestVerboseNameSize = std::max(largestVerboseName->verboseName.size() + 2, verboseName.size() + 2);
        const std::string quickName = "Quick Name";
        const std::string description = "Description";


        // Ausgabe der Tabelle
        std::cout
        << verboseName
        << std::string(largestVerboseNameSize - verboseName.size(), ' ')
        << " | "
        << quickName
        << " | "
        << description
        << std::endl;

        for (auto const& cmd : commands) {
        std::cout
        << cmd.verboseName
        << std::string(largestVerboseNameSize - cmd.verboseName.size(), ' ')
        << " | "
        << cmd.quickName
        << std::string(quickName.size() - cmd.quickName.size(), ' ')
        << " | "
        << cmd.description << std::endl;
        }
    }

    auto addPredefinedCommands() -> void {
        const Command quitCommand{
                .id = ReservedCommands::QUIT_ID,
                .verboseName = "--quit",
                .quickName = "-q",
                .description = "Exits the program.",
                .function = []([[maybe_unused]] std::vector<std::string> const& args) {
                    exit(0);
                }};
        commands.push_back(quitCommand);

        const Command helpCommand{
                .id = ReservedCommands::HELP_ID,
                .verboseName = "--help",
                .quickName = "-h",
                .description = "Gives you a helpful overview about the commands.",
                .function = std::bind_front(&CommandHandler::showHelp, this)
        };
        commands.push_back(helpCommand);

        const Command versionCommand{
                .id = ReservedCommands::VERSION_ID,
                .verboseName = "--version",
                .quickName = "-v",
                .description = "Gives you the version of the program.",
                .function = []([[maybe_unused]] std::vector<std::string> const& args) {
                    std::cout << "This is a version command." << std::endl;
                }};
        commands.push_back(versionCommand);

        const Command verboseCommand{
                .id = ReservedCommands::VERBOSE_ID,
                .verboseName = "--verbose",
                .quickName = "-V",
                .description = "Enabled more information if you use a command.",
                .function = [this]([[maybe_unused]] std::vector<std::string> const& args) {
                    this->isVerbose = true;
                }};
        commands.push_back(verboseCommand);
    }

public:
    explicit CommandHandler(std::vector<std::string> const& args) : rawArgs(args) {
        addPredefinedCommands();

    }

    auto add(Command const& command) {
        commands.push_back(command);
    }

    auto execute() -> void {
        getTotalCommand();

        switch(totalCommand) {
            case ReservedCommands::VERBOSE_ID:
                std::cout << "Verbose mode is enabled." << std::endl;

            [[fallthrough]]
            case ReservedCommands::QUIT_ID:
                std::cout << "No command to execute." << std::endl;
                exit(0);
                break;

            case ReservedCommands::HELP_ID:
                showHelp({});
                break;

            default:
                executeInOrder();
                break;
        }
    }


};
