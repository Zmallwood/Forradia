/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "common.hpp"

_NS_START_
namespace Common
{
    void SDLDeleter::operator()(SDL_Window *window) const
    {
        // Free up resources from a SDL_Window object.
        SDL_DestroyWindow(window);
    }

    void SDLDeleter::operator()(SDL_Renderer *renderer) const
    {
        // Free up resources from a SDL_Renderer object.
        SDL_DestroyRenderer(renderer);
    }

    void SDLDeleter::operator()(SDL_Surface *surface) const
    {
        // Free up resources from a SDL_Surface object.
        SDL_FreeSurface(surface);
    }

    void SDLDeleter::operator()(SDL_Texture *texture) const
    {
        // Free up resources from a SDL_Texture object.
        SDL_DestroyTexture(texture);
    }

    void SDLDeleter::operator()(TTF_Font *font) const
    {
        // Free up resources from a TTF_Font object.
        TTF_CloseFont(font);
    }

    namespace Matter
    {
        bool Point::operator==(const Point &other) const
        {
            // Compare x and y dimensions.
            return other.x == x && other.y == y;
        }

        PointF PointF::operator+(const PointF &other) const
        {
            // Sum the dimensions of the two points.
            return {x + other.x, y + other.y};
        }

        PointF PointF::operator-(const PointF &other) const
        {
            // Subract the dimensions of the other point from this point.
            return {x - other.x, y - other.y};
        }

        bool RectF::Contains(PointF point)
        {
            // Create condition by checking against the boundaries of this
            // rectangle.
            return point.x >= x && point.y >= y && point.x < x + width &&
                   point.y < y + height;
        }

        PointF RectF::GetPosition() const
        {
            // Return only the coordinates.
            return {x, y};
        }

        void RectF::Offset(PointF offset)
        {
            // Add the offset to the dimensions separately.
            x += offset.x;
            y += offset.y;
        }
        namespace Coloring
        {
            SDL_Color Color::ToSDLColor() const
            {
                // Calculate individual color components.
                auto rUint{CUint8(r * 255)};
                auto gUint{CUint8(g * 255)};
                auto bUint{CUint8(b * 255)};
                auto aUint{CUint8(a * 255)};

                return {rUint, rUint, bUint, aUint};
            }
        }
    }
    namespace Utilities
    {
        namespace CanvasUtilities
        {
            // Canvas util functions
            Size GetCanvasSize(SharedPtr<SDL_Window> window)
            {
                Size canvasSize;

                // Get the size of the window.
                SDL_GetWindowSize(window.get(), &canvasSize.width,
                                  &canvasSize.height);

                return canvasSize;
            }

            float CalcAspectRatio(SharedPtr<SDL_Window> window)
            {
                auto canvasSize{GetCanvasSize(window)};

                // Calculate the aspect ratio.
                auto aspectRatio{CFloat(canvasSize.width) / canvasSize.height};

                return aspectRatio;
            }

            float ConvertWidthToHeight(float width,
                                       SharedPtr<SDL_Window> window)
            {
                // Calculate the height based on the width and the aspect ratio.
                return width * CalcAspectRatio(window);
            }

            float ConvertHeightToWidth(float height,
                                       SharedPtr<SDL_Window> window)
            {
                // Calculate the width based on the height and the aspect ratio.
                return height / CalcAspectRatio(window);
            }
        }
        namespace FilePathUtilities
        {
            // File path util functions
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
                auto nameWithExtension{
                    String(path.substr(path.find_last_of('/') + 1))};

                return nameWithExtension.substr(
                    0, nameWithExtension.find_last_of('.'));
            }
        }
        namespace MouseUtilities
        {
            // Mouse util functions
            PointF GetNormallizedMousePosition(SharedPtr<SDL_Window> window)
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
        }
        namespace NumbersUtilities
        {
            // Numbers util functions
            float InvertMovementSpeed(float movemenSpeed)
            {
                // Calculate the inverse of the movement speed.
                if (movemenSpeed)
                {
                    // If the movement speed is not zero, invert it and return.
                    return k_oneSecMillis / movemenSpeed;
                }
                else
                {
                    // If the movement speed is zero, avoid division by zero
                    // and return zero directly instead.
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
        }
        namespace RandomizationUtilities
        {
            // Randomization util functions
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
        }
        namespace StringUtilities
        {
            // String util functions
            String Replace(StringView text, char replace, char replaceWith)
            {
                String result{text.data()};

                // Replace all instances of repl with repl_with.
                std::replace(result.begin(), result.end(), replace,
                             replaceWith);

                return result;
            }
        }
        namespace TimeUtilities
        {
            // Time util functions
            int GetTicks()
            {
                // Get the number of ticks.
                return SDL_GetTicks();
            }
        }
        namespace HashUtilities
        {
            // Hash util functions
            int Hash(StringView text)
            {
                // Use algorithm from source which is forgotten what it was.
                unsigned long hash{5381};

                for (size_t i = 0; i < text.size(); ++i)
                {
                    hash = 33 * hash + (unsigned char)text[i];
                }

                return CInt(hash);
            }
        }
        namespace PrintUtilities
        {
            // Print util functions
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
    }
}
_NS_END_