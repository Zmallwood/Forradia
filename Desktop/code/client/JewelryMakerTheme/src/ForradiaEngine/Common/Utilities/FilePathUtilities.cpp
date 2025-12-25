/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "FilePathUtilities.hpp"
// clang-format on

namespace Forradia
{
    auto getFileExtension(std::string_view path) -> std::string
    {
        std::string extension{path.substr(path.find_last_of('.') + 1).data()};

        return extension;
    }

    auto getFileNameNoExtension(std::string_view path) -> std::string
    {
        auto nameWithExtension{std::string(path.substr(path.find_last_of('/') + 1))};

        return nameWithExtension.substr(0, nameWithExtension.find_last_of('.'));
    }
}
