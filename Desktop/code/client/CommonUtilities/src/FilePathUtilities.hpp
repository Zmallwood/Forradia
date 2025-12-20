/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once
#include <string>

namespace Forradia {
    /**
     * Get the file extension from a given path.
     *
     * @param path Path to the file.
     * @return File extension.
     */
    auto GetFileExtension(std::string_view path) -> std::string;

    /**
     * Get the file name without the extension.
     *
     * @param path Path to the file.
     * @return File name without the extension.
     */
    auto GetFileNameNoExtension(std::string_view path) -> std::string;
}
