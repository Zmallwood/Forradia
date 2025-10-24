//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Common.hpp"
#include "Constants.hpp"
#include "Utilities/CanvasUtilities.hpp"
#include "Utilities/CastUtilities.hpp"

namespace Forradia
{
    String GetFileExtension(StringView path)
    {
        // Get the file extension.
        String extension{
            path.substr(path.find_last_of('.') + 1).data()};

        return extension;
    }

    String GetFileNameNoExtension(StringView path)
    {
        // Get the file name without the extension.
        auto nameWithExtension{String(
            path.substr(path.find_last_of('/') + 1))};

        return nameWithExtension.substr(
            0, nameWithExtension.find_last_of('.'));
    }

    PointF GetNormallizedMousePosition(
        SharedPtr<SDL_Window> window)
    {
        int xPx;
        int yPx;

        // Get the mouse position.
        SDL_GetMouseState(&xPx, &yPx);
        auto canvasSize{GetCanvasSize(window)};

        // Calculate the normalized mouse position.
        return {CFloat(xPx) / canvasSize.width,
                CFloat(yPx) / canvasSize.height};
    }

    float InvertMovementSpeed(float movemenSpeed)
    {
        // Calculate the inverse of the movement speed.
        if (movemenSpeed)
        {
            // If the movement speed is not zero, invert it
            // and return.
            return k_oneSecMillis / movemenSpeed;
        }
        else
        {
            // If the movement speed is zero, avoid division
            // by zero and return zero directly instead.
            return 0.0f;
        }
    }

    int Normalize(int value)
    {
        auto absValue{std::abs(value)};
        auto normalized{0};

        // Calculate the normalized value.
        if (value)
        {
            normalized = value / absValue;
        }

        return normalized;
    }

    float Ceil(float number, float k)
    {
        // Calculate the ceiled value with k decimal places.
        auto p{std::pow(10.0, k)};

        return std::ceil(number * p) / p;
    }

    void Randomize()
    {
        // Randomize the seed.
        srand(time(nullptr));
    }

    int GetRandomInt(int upperLimit)
    {
        // Generate a random integer.
        return rand() % upperLimit;
    }

    String Replace(StringView text, char replace,
                   char replaceWith)
    {
        String result{text.data()};

        // Replace all instances of repl with repl_with.
        std::replace(result.begin(), result.end(), replace,
                     replaceWith);

        return result;
    }

    int GetTicks()
    {
        // Get the number of ticks.
        return SDL_GetTicks();
    }

    int Hash(StringView text)
    {
        // Use algorithm from source which is forgotten what
        // it was.
        unsigned long hash{5381};

        for (size_t i = 0; i < text.size(); ++i)
        {
            hash = 33 * hash + (unsigned char)text[i];
        }

        return CInt(hash);
    }

    void Print(StringView text)
    {
        // Print out text without a following line break.
        std::cout << text;
    }

    void PrintLine(StringView text)
    {
        // Print out text with a following line break.
        std::cout << text << std::endl;
    }
}