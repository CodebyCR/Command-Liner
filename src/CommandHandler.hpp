//
// Created by Christoph Rohde on 02.02.24.
//

#pragma once


#include "Option.hpp"
#include "ReservedOptions.hpp"
#include <iostream>
#include <ranges>
#include <vector>
#include <sstream>


class CommandHandler {
private:
    std::vector<std::string> rawArgs;
    std::uint64_t totalOption = {0};
    std::vector<Option> options;
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

        for(auto const& opt: options) {
            if(opt.id & totalOption) {
                std::cout << opt.function(filteredArgs) << std::endl;
            }
        }
    }

    auto getRawOptions() -> std::vector<std::string> {
        std::vector<std::string> rawOptions;
        // drop the first argument, which is the program name
        rawArgs.erase(rawArgs.begin());

        std::ranges::copy_if(rawArgs, std::back_inserter(rawOptions), [](auto const& arg) {
            return arg.starts_with('-');
        });

        return rawOptions;
    }

    /// Check if the command is a combined quick command like -hv or -Vvh
    auto isCombinedQuickOption(std::string_view option) -> bool {
        const bool dontFoundDoubleDash = option.find("--");
        const bool moreThanTwoChars = std::ranges::size(option) > 2;
        return dontFoundDoubleDash && moreThanTwoChars;
    }

    auto getTotalOption() {
        /// Handle combined quick options like -hv
        const auto rawOptions = getRawOptions();

        for(auto const& rawOption: rawOptions) {
            //std::cout << "Raw Command: " << rawCommand << std::endl;
            if(isCombinedQuickOption(rawOption)) {
                // if(isVerbose) {
                //  std::cout << "Combined quick command: " << rawCommand << std::endl;
                // }
                for(auto const& symbol: rawOption) {
                    for(auto const& opt: options) {
                        if(symbol == opt.quickName[1]) {
                            this->totalOption = this->totalOption + opt.id;
                        }
                    }
                }
            }

            for(auto const& opt: options) {
                if(rawOption == opt.verboseName || rawOption == opt.quickName) {
                    this->totalOption = this->totalOption + opt.id;
                }
            }
        }
    }

    auto showHelp([[maybe_unused]] std::vector<std::string> const& args) -> std::string {
        // sort options by cmd.quickName case-insensitive
        std::sort(options.begin(), options.end(), [](auto const& a, auto const& b) {
            return std::lexicographical_compare(a.quickName.begin(), a.quickName.end(), b.quickName.begin(), b.quickName.end(), [](char a, char b) {
                return std::tolower(a) < std::tolower(b);
            });
        });

        if(totalOption != ReservedOptions::HELP_ID) {
            /// Remove all options that are not in the totalCommand
            options.erase(std::remove_if(options.begin(), options.end(), [this](auto const& opt) {
                              return !(opt.id & this->totalOption);
                          }),
                          options.end());
        }


        const auto largestVerboseName = std::ranges::max_element(options, {}, [](auto const& opt) {
            return opt.verboseName.size();
        });

        const std::string verboseName = "Verbose Name";
        const auto largestVerboseNameSize = std::max(largestVerboseName->verboseName.size() + 2, verboseName.size() + 2);
        const std::string quickName = "Quick Name";
        const std::string description = "Description";


        // Ausgabe der Tabelle
        std::stringstream ss;
        ss
                << verboseName
                << std::string(largestVerboseNameSize - verboseName.size(), ' ')
                << " | "
                << quickName
                << " | "
                << description
                << std::endl;

        for(auto const& opt: options) {
            ss
                    << opt.verboseName.data()
                    << std::string(largestVerboseNameSize - opt.verboseName.size(), ' ')
                    << " | "
                    << opt.quickName.data()
                    << std::string(quickName.size() - opt.quickName.size(), ' ')
                    << " | "
                    << opt.description.data() << std::endl;
        }

        return ss.str();
    }

    auto addPredefinedOptions() -> void {
        const Option quitOption{
                .id = ReservedOptions::QUIT_ID,
                .verboseName = "--quit",
                .quickName = "-q",
                .description = "Exits the program.",
                .function = []([[maybe_unused]] std::vector<std::string> const& args) {
                    exit(0);
                    [[no_return]]
                    return "Exit";
                }};
        options.push_back(quitOption);

        const Option helpOption{
                .id = ReservedOptions::HELP_ID,
                .verboseName = "--help",
                .quickName = "-h",
                .description = "Gives you a helpful overview about the options.",
                .function = std::bind_front(&CommandHandler::showHelp, this)};
        options.push_back(helpOption);

        const Option versionOption{
                .id = ReservedOptions::VERSION_ID,
                .verboseName = "--version",
                .quickName = "-v",
                .description = "Gives you the version of the program.",
                .function = []([[maybe_unused]] std::vector<std::string> const& args) {
                    return "This is a version option.\n";
                }};
        options.push_back(versionOption);

        const Option verboseOption{
                .id = ReservedOptions::VERBOSE_ID,
                .verboseName = "--verbose",
                .quickName = "-V",
                .description = "Enabled more information if you use a option.",
                .function = [this]([[maybe_unused]] std::vector<std::string> const& args) {
                    this->isVerbose = true;
                    return "Verbose mode is enabled.";
                }};
        options.push_back(verboseOption);
    }

public:
    explicit CommandHandler(std::vector<std::string> const& args) : rawArgs(args) {
        addPredefinedOptions();
    }

    auto add(Option const& option) {
        options.push_back(option);
    }

    auto execute() -> void {
        getTotalOption();

        switch(totalOption) {
            case ReservedOptions::VERBOSE_ID:
                std::cout << "Verbose mode is enabled." << std::endl;
                break;

            case ReservedOptions::HELP_ID:
                showHelp({});
                break;

            default:

//                std::cout << "Filtered Args: ";
//                for(auto arg: getFilteredArgs()) {
//                    std::cout << arg << std::endl;
//                }

                executeInOrder();
                break;
        }
    }
};
