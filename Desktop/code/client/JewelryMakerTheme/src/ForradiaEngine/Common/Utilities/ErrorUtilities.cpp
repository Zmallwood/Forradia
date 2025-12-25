/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "ErrorUtilities.hpp"
    #include <stdexcept>
    #include <string>
// clang-format on

namespace Forradia
{
    void throwError(std::string_view message, std::source_location loc)
    {
        auto filePath{std::string(loc.file_name())};

        auto onlyName{std::string(filePath.substr(filePath.find_last_of('/') + 1))};

        auto fullMessage{std::string("Error occurred at ") + onlyName + ", line " +
                         std::to_string(loc.line()) + ":\n\"" + message.data() + "\""};

        throw std::runtime_error(fullMessage);
    }

    void throwOnFalse(bool condition, std::string_view message, std::source_location loc)
    {
        if (condition == false)
        {
            throwError(message, loc);
        }
    }
}
