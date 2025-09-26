#pragma once

namespace Forradia
{
    std::string Replace(std::string_view text,
                        char replaced,
                        char replacedWith);

    std::string GetFileExtension(std::string_view path);

    std::string GetFileNameNoExtension(std::string_view path);
}
