/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ErrorUtilities.hpp"

namespace Forradia {
    void PrintError(std::string_view message, std::source_location loc) {
        std::cerr << "Error at " << std::string(loc.file_name()) + ", line " << loc.line() << ":\n"
                  << message << std::endl;
    }
}
