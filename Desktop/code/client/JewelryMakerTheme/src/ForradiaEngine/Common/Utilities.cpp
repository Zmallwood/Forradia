/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Utilities.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>

namespace ForradiaEngine
{
    auto throwError(std::string_view message, std::source_location loc) -> void
    {
        auto filePath{std::string(loc.file_name())};

        auto onlyName{std::string(filePath.substr(filePath.find_last_of('/') + 1))};

        auto fullMessage{std::string("Error occurred at ") + onlyName + ", line " +
                         std::to_string(loc.line()) + ":\n\"" + message.data() + "\""};

        throw std::runtime_error(fullMessage);
    }

    auto throwOnFalse(bool condition, std::string_view message, std::source_location loc) -> void
    {
        if (condition == false)
        {
            throwError(message, loc);
        }
    }

    auto invertSpeed(float speed) -> float
    {
        auto result{0.0F};

        if (speed != 0.0F)
        {
            result = k_oneSecMillis / speed;
        }

        return result;
    }

    auto normalize(int value) -> int
    {
        auto absValue{std::abs(value)};
        auto normalized{0};

        if (value != 0)
        {
            normalized = value / absValue;
        }

        return normalized;
    }

    auto ceil(float number, float numDecimalPlaces) -> float
    {
        const auto powBase{10.0F};

        auto factor{std::pow(powBase, numDecimalPlaces)};

        return std::ceil(number * factor) / factor;
    }

    auto computeNormal(const glm::vec3 &vec1, const glm::vec3 &vec2, const glm::vec3 &vec3)
        -> glm::vec3
    {
        // Uses vec2 as a new origin for vec1, vec3.
        auto vecA = vec3 - vec2;
        auto vecB = vec1 - vec2;

        // Compute the cross product vecA X vecB to get the face normal.
        return glm::normalize(glm::cross(vecA, vecB));
    }

    auto replace(std::string_view text, char replace, char replaceWith) -> std::string
    {
        std::string result{text.data()};

        std::replace(result.begin(), result.end(), replace, replaceWith);

        return result;
    }

    auto print(std::string_view text) -> void
    {
        std::cout << text;
    }

    auto printLine(std::string_view text) -> void
    {
        std::cout << text << std::endl;
    }

    auto randomize() -> void
    {
        srand(time(nullptr));
    }

    auto getRandomInt(int upperLimit) -> int
    {
        return rand() % upperLimit;
    }

    auto getTicks() -> int
    {
        return SDL_GetTicks();
    }

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

    auto getCanvasSize(const std::shared_ptr<SDL_Window> &window) -> Size
    {
        throwOnFalse(window != nullptr, "window is null");

        Size canvasSize;

        SDL_GetWindowSize(window.get(), &canvasSize.width, &canvasSize.height);

        return canvasSize;
    }

    auto calcAspectRatio(const std::shared_ptr<SDL_Window> &window) -> float
    {
        throwOnFalse(window != nullptr, "window is null");

        auto canvasSize{getCanvasSize(window)};

        auto aspectRatio{static_cast<float>(canvasSize.width) /
                         static_cast<float>(canvasSize.height)};

        return aspectRatio;
    }

    auto convertWidthToHeight(float width, const std::shared_ptr<SDL_Window> &window) -> float
    {
        throwOnFalse(window != nullptr, "window is null");

        return width * calcAspectRatio(window);
    }

    auto convertHeightToWidth(float height, const std::shared_ptr<SDL_Window> &window) -> float
    {
        throwOnFalse(window != nullptr, "window is null");

        return height / calcAspectRatio(window);
    }

    auto getNormalizedMousePosition(const std::shared_ptr<SDL_Window> &window) -> PointF
    {
        throwOnFalse(window != nullptr, "window is null");

        int xPx;
        int yPx;

        SDL_GetMouseState(&xPx, &yPx);

        auto canvasSize{getCanvasSize(window)};

        return {static_cast<float>(xPx) / canvasSize.width,
                static_cast<float>(yPx) / canvasSize.height};
    }
}
