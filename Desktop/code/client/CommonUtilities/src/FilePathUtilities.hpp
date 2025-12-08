//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#pragma once
#include "Aliases.hpp"

namespace Forradia
{
    /// Get the file extension.
    ///
    /// @param path  Path to the file.
    /// @return File extension.
    String GetFileExtension(StringView path);

    /// Get the file name without the extension.
    ///
    /// @param path Path to the file.
    /// @return File name without the extension.
    String GetFileNameNoExtension(StringView path);
}