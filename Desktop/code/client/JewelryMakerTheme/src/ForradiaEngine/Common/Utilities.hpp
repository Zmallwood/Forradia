/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <source_location>
#include <string_view>
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include "ForradiaEngine/Common/Matter/Geometry.hpp"

struct SDL_Window;

namespace ForradiaEngine
{
    /**
     *  Throw an error with a given message.
     *
     *  @param message The message to throw.
     *  @param loc The source location of the error, should not be provided manually.
     */
    [[noreturn]] auto throwError(std::string_view message,
                                 std::source_location loc = std::source_location::current())
        -> void;

    /**
     *  Throw an error if a condition is false.
     *
     *  @param condition The condition to check.
     *  @param message The message to throw.
     *  @param loc The source location of the error, should not be provided manually.
     */
    auto throwOnFalse(bool condition, std::string_view message,
                      std::source_location loc = std::source_location::current()) -> void;

    /**
     *  Calculate the inverse of the speed.
     *
     *  @param speed Speed to invert.
     *  @return The inverse of the speed.
     */
    auto invertSpeed(float speed) -> float;

    /**
     *  Calculate the normalized value.
     *
     *  @param value Value to normalize.
     *  @return The normalized value.
     */
    auto normalize(int value) -> int;

    /**
     *  Calculate the ceiled value with a given number of decimal places.
     *
     *  @param number The value to ceil.
     *  @param numDecimalPlaces The number of decimal places.
     *  @return The ceiled value.
     */
    auto ceil(float number, float numDecimalPlaces) -> float;

    /**
     *  Calculate the distance between two points.
     *
     *  @param x1 First x coordinate.
     *  @param y1 First y coordinate.
     *  @param x2 Second x coordinate.
     *  @param y2 Second y coordinate.
     *  @return The distance between the two points.
     */
    auto calcDistance(int xPos1, int yPos1, int xPos2, int yPos2) -> float;

    /**
     *  Compute the normal of a triangle.
     *
     *  @param p1 First point.
     *  @param p2 Second point.
     *  @param p3 Third point.
     *  @return Normal.
     */
    auto computeNormal(const glm::vec3 &vec1, const glm::vec3 &vec2, const glm::vec3 &vec3)
        -> glm::vec3;

    /**
     *  Replace all instances of a character in a string with another character.
     *
     *  @param text String to replace characters in.
     *  @param replace Character to replace.
     *  @param replaceWith Character to replace with.
     *  @return Replaced string.
     */
    auto replace(std::string_view text, char replace, char replaceWith) -> std::string;

    /**
     *  Print out a string of text, without a following line break.
     *
     *  @param text Text to print.
     */
    auto print(std::string_view text) -> void;

    /**
     *  Print out a string of text, with an added line break at the end.
     *
     *  @param text Text to print.
     */
    auto printLine(std::string_view text) -> void;

    /**
     *  Randomize the seed.
     */
    auto randomize() -> void;

    /**
     *  Generate a random integer.
     *
     *  @param upperLimit Upper limit.
     *  @return Random integer.
     */
    auto getRandomInt(int upperLimit) -> int;

    /**
     *  Get the number of ticks.
     *
     *  @return The number of ticks.
     */
    auto getTicks() -> int;

    /**
     *  Get the file extension from a given path.
     *
     *  @param path Path to the file.
     *  @return File extension.
     */
    auto getFileExtension(std::string_view path) -> std::string;

    /**
     *  Get the file name without the extension.
     *
     *  @param path Path to the file.
     *  @return File name without the extension.
     */
    auto getFileNameNoExtension(std::string_view path) -> std::string;

    /**
     * Obtain canvas size in pixels.
     * @param window Window to get the canvas size for.
     * @return The canvas size in pixels.
     */
    auto getCanvasSize(const std::shared_ptr<SDL_Window> &window) -> Size;

    /**
     * Calculate the aspect ratio of a given window.
     * @param window Window to calculate the aspect ratio for.
     * @return The calculated aspect ratio.
     */
    auto calcAspectRatio(const std::shared_ptr<SDL_Window> &window) -> float;

    /**
     * Convert a width to a height based on the width and the aspect ratio.
     * @param width Width to convert.
     * @param window Window to calculate the aspect ratio for.
     * @return The resulting height.
     */
    auto convertWidthToHeight(float width, const std::shared_ptr<SDL_Window> &window) -> float;

    /**
     *  Obtain normalized mouse position.
     *
     *  @param window Window to get the mouse position for.
     *  @return The normalized mouse position.
     */
    auto getNormalizedMousePosition(const std::shared_ptr<SDL_Window> &window) -> PointF;
}
