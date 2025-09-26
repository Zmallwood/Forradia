#include "StringUtilities.hpp"

namespace Forradia
{
    std::string Replace( std::string_view text,
                        char replaced,
                        char replacedWith )
    {
        std::string textData { text.data() };

        std::replace(
            textData.begin(),
            textData.end(),
            replaced,
            replacedWith
        );

        return textData;

    }

    std::string GetFileExtension( std::string_view path )
    {
        std::string extension {
            path.substr( path.find_last_of( '.' ) + 1 ).data()
        };

        return extension;
    }

    std::string GetFileNameNoExtension( std::string_view path )
    {
        auto nameWithExtension {
            std::string(
                path.substr( path.find_last_of( '/' ) + 1 )
            )
        };

        return nameWithExtension.substr(
            0,
            nameWithExtension.find_last_of( '.' )
        );
    }
}
