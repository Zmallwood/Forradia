/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#define _NS_START_                                                             \
    namespace Forradia                                                         \
    {
#define _NS_END_ }

#pragma once
#include <functional>
#include <memory>
#include <string>
#include <vector>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;
typedef struct _TTF_Font TTF_Font;
struct SDL_Color;
typedef uint8_t Uint8;

_NS_START_
namespace Common
{
    namespace Aliases
    {
        // A set of aliases for commonly used types.
        using String = std::string;
        using StringView = std::string_view;
        template <class T> using SharedPtr = std::shared_ptr<T>;
        template <class T> using Vector = std::vector<T>;
        template <class T> using Function = std::function<T>;
    }
    using namespace Aliases;
    namespace Constants
    {
        // Constants that may be used throughout the project.
        static constexpr int k_oneSecMillis{
            1000}; ///< Number of milliseconds in one second.
    }
    using namespace Constants;
    namespace Singletons
    {
        // Singleton functions
        /**
         * Returns a singleton of an object of type T, in the
         * form of a SharedPtr.
         *
         * \tparam T Type to get singleton for.
         * \return The singleton object as a SharedPtr.
         */
        template <class T> SharedPtr<T> __()
        {
            // Create singleton instance only once.
            static SharedPtr<T> instance{std::make_shared<T>()};

            return instance;
        }

        /**
         * Returns a singleton of an object of type T, in the
         * form of a reference.
         *
         * \tparam T Type to get singleton for.
         * \return The singleton object as a reference.
         */
        template <class T> T &_()
        {
            // Use the SharedPtr singleton function to obtain
            // the singleton, but return a reference to it.
            return *__<T>();
        }
    }
    using namespace Singletons;
    namespace HelperClasses
    {
        // Convenience classes
        /**
         * Class used for SharedPtrs of SDL objects,
         * which handles automaticallyfreeing up resources at object deletion.
         */
        class SDLDeleter
        {
          public:
            /**
             * Operator overloading for SDL_Window objects.
             *
             * \param window SDL window pointer to free resources for.
             */
            void operator()(SDL_Window *window) const;

            /**
             * Operator overloading for SDL_Renderer objects.
             *
             * \param renderer SDL renderer pointer to free resources for.
             */
            void operator()(SDL_Renderer *renderer) const;

            /**
             * Operator overloading for SDL_Surface objects.
             *
             * \param surface SDL surface pointer to free resources for.
             */
            void operator()(SDL_Surface *surface) const;

            /**
             * Operator overloading for SDL_Texture objects.
             *
             * \param texture SDL texture pointer to free resources for.
             */
            void operator()(SDL_Texture *texture) const;

            /**
             * Operator overloading for TTF_Font objects.
             *
             * \param font SDL font pointer to free resources for.
             */
            void operator()(TTF_Font *font) const;
        };
    }
    using namespace HelperClasses;
    namespace Matter
    {
        /**
         * Point in 2D space, using dimensions of int type.
         */
        class Point
        {
          public:
            /**
             * Equality operator between two Points.
             *
             * \param other Other Point to check equality against.
             * \return True if the two points are equal, otherwise false.
             */
            bool operator==(const Point &other) const;

            int x{0};
            int y{0};
        };

        /**
         * Point in 2D space using dimensions of float type.
         */
        class PointF
        {
          public:
            /**
             * Summing operator for the two points.
             *
             * \param other The other PointF to add to this point.
             * \return The resulting PointF with the dimensions added
             * separately.
             */
            PointF operator+(const PointF &other) const;

            /**
             * Subtraction operator for the two points.
             *
             * \param other The other PointF to subtract from this point.
             * \return The resulting PointF with the dimensions subtracted
             * separetely.
             */
            PointF operator-(const PointF &other) const;

            float x{0.0f}; ///< The x dimension.
            float y{0.0f}; ///< The y dimension.
        };

        /**
         * Point in 3D space using dimensions of float type.
         */
        class Point3F
        {
          public:
            float x{0.0f}; ///< The x dimension.
            float y{0.0f}; ///< The y dimension.
            float z{0.0f}; ///< The z dimension.
        };

        /**
         * Size in 2D space, with the dimensions as int values.
         */
        class Size
        {
          public:
            int width{0};  ///< Width.
            int height{0}; /// Height.
        };

        /**
         * Size in 2D space with dimensions of float values.
         */
        class SizeF
        {
          public:
            float width{0.0f};  ///< Width.
            float height{0.0f}; ///< Height.
        };

        /**
         * A rectangle in 2D space using dimensions of float type.
         */
        class RectF
        {
          public:
            /**
             * Check if this rectangle contains a certian point.
             *
             * \param point Point to check if it is contained in this rectangle.
             * \return True if the Point is within this rectangle, otherwise
             * false.
             */
            bool Contains(PointF point);

            /**
             * Returns only the position of this rectangle.
             *
             * \return The position.
             */
            PointF GetPosition() const;

            /**
             * Adds an offset to this rectangle, with the dimensions altered
             * separately.
             *
             * \param offset The offset to add.
             */
            void Offset(PointF offset);

            float x{0.0f};      ///< The x coordinate.
            float y{0.0f};      ///< The y coordinate.
            float width{0.0f};  ///< The width, in the x dimension.
            float height{0.0f}; ///< The height, in the y dimension.
        };
        namespace Coloring
        {
            /**
             * A RGBA color with components defined with float values.
             */
            class Color
            {
              public:
                /**
                 * Convert this color to a corresponding SDL_Color object.
                 *
                 * \return Corresponding SDL_Color object.
                 */
                SDL_Color ToSDLColor() const;

                float r{0.0f};
                float g{0.0f};
                float b{0.0f};
                float a{0.0f};
            };

            /**
             * Contains a palette of colors.
             */
            namespace Colors
            {
                constexpr Color Black{0.0f, 0.0f, 0.0f, 1.0f}; ///< Black color.

                constexpr Color Wheat{1.0f, 1.0f, 0.65f,
                                      1.0f}; ///< Wheat color.

                constexpr Color WheatTransparent{
                    1.0f, 1.0f, 0.65f, 0.7f}; ///< Transparent wheat color.

                constexpr Color Yellow{1.0f, 1.0f, 0.0f,
                                       1.0f}; ///< Yellow color.

                constexpr Color YellowTransparent{
                    1.0f, 1.0f, 0.0f, 0.7f}; ///< Transparent yellow color.
            }
        }
        using namespace Coloring;
    }
    using namespace Matter;
    namespace Utilities
    {
        namespace CanvasUtilities
        {
            // Canvas util functions
            Size GetCanvasSize(SharedPtr<SDL_Window> window);

            /**
             * Calculate the aspect ratio of a given window.
             *
             * \param window Window to calculate the aspect ratio for.
             * \return The calculated aspect ratio.
             */
            float CalcAspectRatio(SharedPtr<SDL_Window> window);

            /**
             * Convert a width to a height based on the width and the aspect
             * ratio.
             *
             * \param width Width to convert.
             * \param window Window to calculate the aspect ratio for.
             * \return The resulting height.
             */
            float ConvertWidthToHeight(float width,
                                       SharedPtr<SDL_Window> window);

            /**
             * Convert a height to a width base on the height and the aspect
             * ratio.
             *
             * \param height Height to convert.
             * \param window Window to calculate the aspect ratio for.
             * \return The resulting width.
             */
            float ConvertHeightToWidth(float height,
                                       SharedPtr<SDL_Window> window);
        }
        using namespace CanvasUtilities;
        namespace FilePathUtilities
        {
            // File path util functions
            String GetFileExtension(StringView path);

            String GetFileNameNoExtension(StringView path);
        }
        using namespace FilePathUtilities;
        namespace MouseUtilities
        {
            // Mouse util functions
            PointF GetNormallizedMousePosition(SharedPtr<SDL_Window> window);
        }
        using namespace MouseUtilities;
        namespace NumbersUtilities
        {
            // Numbers util functions
            float InvertMovementSpeed(float movementSpeed);

            int Normalize(int value);

            float Ceil(float number, float k);
        }
        using namespace NumbersUtilities;
        namespace RandomizationUtilities
        {
            // Randomization util functions
            void Randomize();

            int GetRandomInt(int upperLimit);
        }
        using namespace RandomizationUtilities;
        namespace StringUtilities
        {
            // String util functions
            String Replace(StringView text, char replace, char replaceWith);
        }
        using namespace StringUtilities;
        namespace TimeUtilities
        {
            // Time util functions
            int GetTicks();
        }
        using namespace TimeUtilities;
        namespace HashUtilities
        {
            // Hash util functions
            /**
             * Compute hash code from a given input text, which
             * gets computed the same every game start.
             *
             * \param text Text to compute hash code for.
             * \return Computed hash code.
             */
            int Hash(StringView text);
        }
        using namespace HashUtilities;
        namespace PrintUtilities
        {
            // Print util functions
            /**
             * Print out a string of text, without a following line break.
             *
             * \param text Text to print.
             */
            void Print(StringView text);

            /**
             * Print out a string of text, with an added line break at the end.
             *
             * \param text Text to print.
             */
            void PrintLine(StringView text);
        }
        using namespace PrintUtilities;
        namespace CastUtilities
        {
            // Cast util functions
            /**
             * Cast a value to int.
             *
             * \param value Value to cast.
             * \return Casted value.
             */
            constexpr int CInt(auto value)
            {
                return static_cast<int>(value);
            }

            /**
             * Cast a value to float.
             *
             * \param value Value to cast.
             * \return Casted value.
             */
            float CFloat(auto value)
            {
                return static_cast<float>(value);
            }

            /**
             * Cast a value to Uint8.
             *
             * \param value Value to cast.
             * \return Casted value.
             */
            Uint8 CUint8(auto value)
            {
                return static_cast<Uint8>(value);
            }
        }
        using namespace CastUtilities;
    }
    using namespace Utilities;
}
using namespace Common;
_NS_END_