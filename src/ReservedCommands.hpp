//
// Created by Christoph Rohde on 25.02.24.
//

#pragma once

#include <iostream>


namespace ReservedCommands{
    /// 2^0
    constexpr std::uint64_t QUIT_ID = {0};
    /// 2^60
    constexpr std::uint64_t VERSION_ID = {0x10'00'00'00'00'00'00'00};
    /// 2^61
    constexpr std::uint64_t VERBOSE_ID  = {0x20'00'00'00'00'00'00'00};
    /// 2^62
    constexpr std::uint64_t HELP_ID = {0x40'00'00'00'00'00'00'00};
    /// 2^63
    constexpr std::uint64_t getUnknownId {0x80'00'00'00'00'00'00'00};
}
