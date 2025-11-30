//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "FilePathUtilities.hpp"

namespace AAK
{
    namespace Forradia
    {
        String GetFileExtension(StringView path)
        {
            // Get the file extension by finding the last dot in the path.

            String extension{path.substr(path.find_last_of('.') + 1).data()};

            return extension;
        }

        String GetFileNameNoExtension(StringView path)
        {
            // Get the file name, without the extension, by finding the last slash in the path and
            // then the last dot.

            auto nameWithExtension{String(path.substr(path.find_last_of('/') + 1))};

            return nameWithExtension.substr(0, nameWithExtension.find_last_of('.'));
        }
    }
}