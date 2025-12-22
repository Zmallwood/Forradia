/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ErrorUtilities.hpp"

namespace Forradia {
    void ThrowError(std::string_view message, std::source_location loc) {
        auto filePath{std::string(loc.file_name())};
        auto onlyName{std::string(path.substr(path.find_last_of('/') + 1))};
        std::cerr << "Error at " << onlyName + ", line " << loc.line() << ":\n"
                  << message << std::endl;
        throw std::runtime_error(std::string(message));
    }
}
