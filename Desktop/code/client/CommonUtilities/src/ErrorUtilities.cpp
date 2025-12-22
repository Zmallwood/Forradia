/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ErrorUtilities.hpp"
#include <string>

namespace Forradia
{
    void ThrowError(std::string_view message, std::source_location loc)
    {
        auto filePath{std::string(loc.file_name())};

        auto onlyName{std::string(filePath.substr(filePath.find_last_of('/') + 1))};

        auto fullMessage{std::string("Error occurred at ") + onlyName + ", line " +
                         std::to_string(loc.line()) + ":\n\"" + message.data() + "\""};

        throw std::runtime_error(fullMessage);
    }
}
