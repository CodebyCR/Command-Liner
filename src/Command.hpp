//
// Created by Christoph Rohde on 18.02.24.
//

#pragma once

#include <functional>
#include <string>

struct Command {
    std::uint64_t id;
    std::string_view verboseName;
    std::string_view quickName;
    std::string_view description;
    std::function<void(std::vector<std::string>)> function;
};
