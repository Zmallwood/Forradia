/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "FilePathUtilities.hpp"

namespace Forradia
{
    std::string GetFileExtension(std::string_view path)
    {
        std::string extension{
            path.substr(path.find_last_of('.') + 1).data()};

        return extension;
    }

    std::string GetFileNameNoExtension(std::string_view path)
    {
        auto nameWithExtension{
            std::string(
                path.substr(path.find_last_of('/') + 1))};

        return nameWithExtension.substr(
            0,
            nameWithExtension.find_last_of('.'));
    }
}