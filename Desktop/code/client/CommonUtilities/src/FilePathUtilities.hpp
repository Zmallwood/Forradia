/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "Aliases.hpp"

namespace Forradia {
/// Get the file extension.
///
/// @param path  Path to the file.
/// @return File extension.
auto GetFileExtension(StringView path) -> String;

/// Get the file name without the extension.
///
/// @param path Path to the file.
/// @return File name without the extension.
auto GetFileNameNoExtension(StringView path) -> String;
}