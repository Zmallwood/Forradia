/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#define _NS_START_                                                             \
    namespace Forradia                                                         \
    {                                                                          \
        namespace gui_test                                                     \
        {                                                                      \
        }
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
    ////////////////////
    // Convenience
    ////////////////////
    namespace Aliases
    {
        // A set of aliases for commonly used types.
        using str = std::string;
        using str_view = std::string_view;
        template <class T> using s_ptr = std::shared_ptr<T>;
        template <class T> using vec = std::vector<T>;
        template <class T> using func = std::function<T>;
    }
    using namespace Aliases;
    namespace Constants
    {
        // Constants that may be used throughout the project.
        static constexpr int k_one_sec_millis{
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
        template <class T> s_ptr<T> __()
        {
            // Create singleton instance only once.
            static s_ptr<T> inst = std::make_shared<T>();
            return inst;
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
        class sdl_del
        {
          public:
            /**
             * Operator overloading for SDL_Window objects.
             *
             * \param win SDL window pointer to free resources for.
             */
            void operator()(SDL_Window *win) const;

            /**
             * Operator overloading for SDL_Renderer objects.
             *
             * \param rend SDL renderer pointer to free resources for.
             */
            void operator()(SDL_Renderer *rend) const;

            /**
             * Operator overloading for SDL_Surface objects.
             *
             * \param surf SDL surface pointer to free resources for.
             */
            void operator()(SDL_Surface *surf) const;

            /**
             * Operator overloading for SDL_Texture objects.
             *
             * \param tex SDL texture pointer to free resources for.
             */
            void operator()(SDL_Texture *tex) const;

            /**
             * Operator overloading for TTF_Font objects.
             *
             * \param font SDL font pointer to free resources for.
             */
            void operator()(TTF_Font *font) const;
        };
    }
    using namespace HelperClasses;
    ////////////////////
    // Matter
    ////////////////////
    namespace Matter
    {
        /**
         * Point in 2D space, using dimensions of int type.
         */
        class pt
        {
          public:
            /**
             * Equality operator between two Points.
             *
             * \param p Other Point to check equality against.
             * \return True if the two points are equal, otherwise false.
             */
            bool operator==(const pt &p) const;

            int x{0};
            int y{0};
        };

        /**
         * Point in 2D space using dimensions of float type.
         */
        class pt_f
        {
          public:
            /**
             * Summing operator for the two points.
             *
             * \param p The other PointF to add to this point.
             * \return The resulting PointF with the dimensions added
             * separately.
             */
            pt_f operator+(const pt_f &p) const;

            /**
             * Subtraction operator for the two points.
             *
             * \param p The other PointF to subtract from this point.
             * \return The resulting PointF with the dimensions subtracted
             * separetely.
             */
            pt_f operator-(const pt_f &p) const;

            float x{0.0f}; ///< The x dimension.
            float y{0.0f}; ///< The y dimension.
        };

        /**
         * Point in 3D space using dimensions of float type.
         */
        class pt3_f
        {
          public:
            float x{0.0f}; ///< The x dimension.
            float y{0.0f}; ///< The y dimension.
            float z{0.0f}; ///< The z dimension.
        };

        /**
         * Size in 2D space, with the dimensions as int values.
         */
        class sz
        {
          public:
            int w{0}; ///< Width.
            int h{0}; /// Height.
        };

        /**
         * Size in 2D space with dimensions of float values.
         */
        class sz_f
        {
          public:
            float w{0.0f}; ///< Width.
            float h{0.0f}; ///< Height.
        };

        /**
         * A rectangle in 2D space using dimensions of float type.
         */
        class rect_f
        {
          public:
            /**
             * Check if this rectangle contains a certian point.
             *
             * \param p Point to check if it is contained in this rectangle.
             * \return True if the Point is within this rectangle, otherwise
             * false.
             */
            bool contains(pt_f p);

            /**
             * Returns only the position of this rectangle.
             *
             * \return The position.
             */
            pt_f pos() const;

            /**
             * Adds an offset to this rectangle, with the dimensions altered
             * separately.
             *
             * \param offs The offset to add.
             */
            void offs(pt_f offs);

            float x{0.0f}; ///< The x coordinate.
            float y{0.0f}; ///< The y coordinate.
            float w{0.0f}; ///< The width, in the x dimension.
            float h{0.0f}; ///< The height, in the y dimension.
        };
        namespace Coloring
        {
            /**
             * A RGBA color with components defined with float values.
             */
            class color
            {
              public:
                /**
                 * Convert this color to a corresponding SDL_Color object.
                 *
                 * \return Corresponding SDL_Color object.
                 */
                SDL_Color to_sdl_color() const;

                float r{0.0f};
                float g{0.0f};
                float b{0.0f};
                float a{0.0f};
            };

            /**
             * Contains a palette of colors.
             */
            namespace colors
            {
                constexpr color black{0.0f, 0.0f, 0.0f, 1.0f}; ///< Black color.

                constexpr color wheat{1.0f, 1.0f, 0.65f,
                                      1.0f}; ///< Wheat color.

                constexpr color wheat_transp{
                    1.0f, 1.0f, 0.65f, 0.7f}; ///< Transparent wheat color.

                constexpr color yellow{1.0f, 1.0f, 0.0f,
                                       1.0f}; ///< Yellow color.

                constexpr color yellow_transp{
                    1.0f, 1.0f, 0.0f, 0.7f}; ///< Transparent yellow color.
            }
        }
        using namespace Coloring;
    }
    using namespace Matter;
    namespace Utilities
    {
        ////////////////////
        // Utils
        ////////////////////
        namespace CanvasUtilities
        {
            // Canvas util functions
            sz get_canv_sz(s_ptr<SDL_Window> win);

            /**
             * Calculate the aspect ratio of a given window.
             *
             * \param win Window to calculate the aspect ratio for.
             * \return The calculated aspect ratio.
             */
            float calc_aspect_ratio(s_ptr<SDL_Window> win);

            /**
             * Convert a width to a height based on the width and the aspect
             * ratio.
             *
             * \param w Width to convert.
             * \param win Window to calculate the aspect ratio for.
             * \return The resulting height.
             */
            float conv_w_to_h(float w, s_ptr<SDL_Window> win);

            /**
             * Convert a height to a width base on the height and the aspect
             * ratio.
             *
             * \param h Height to convert.
             * \param win Window to calculate the aspect ratio for.
             * \return The resulting width.
             */
            float conv_h_to_w(float h, s_ptr<SDL_Window> win);
        }
        using namespace CanvasUtilities;
        namespace FilePathUtilities
        {
            // File path util functions
            str file_ext(str_view path);

            str file_name_no_ext(str_view path);
        }
        using namespace FilePathUtilities;
        namespace MouseUtilities
        {
            // Mouse util functions
            pt_f norm_mouse_pos(s_ptr<SDL_Window> win);
        }
        using namespace MouseUtilities;
        namespace NumbersUtilities
        {
            // Numbers util functions
            float inv_movem_spd(float num);

            int normalize(int val);

            float ceil(float num, float k);
        }
        using namespace NumbersUtilities;
        namespace RandomizationUtilities
        {
            // Randomization util functions
            void randomize();

            int rand_int(int upper_lim);
        }
        using namespace RandomizationUtilities;
        namespace StringUtilities
        {
            // String util functions
            str repl(str_view text, char repl, char repl_with);
        }
        using namespace StringUtilities;
        namespace TimeUtilities
        {
            // Time util functions
            int ticks();
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
            int hash(str_view text);
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
            void print(str_view text);

            /**
             * Print out a string of text, with an added line break at the end.
             *
             * \param text Text to print.
             */
            void print_ln(str_view text);
        }
        using namespace PrintUtilities;
        namespace CastUtilities
        {
            // Cast util functions
            /**
             * Cast a value to int.
             *
             * \param val Value to cast.
             * \return Casted value.
             */
            constexpr int c_int(auto val) { return static_cast<int>(val); }

            /**
             * Cast a value to float.
             *
             * \param val Value to cast.
             * \return Casted value.
             */
            float c_float(auto val) { return static_cast<float>(val); }

            /**
             * Cast a value to Uint8.
             *
             * \param val Value to cast.
             * \return Casted value.
             */
            Uint8 c_uint8(auto val) { return static_cast<Uint8>(val); }
        }
        using namespace CastUtilities;
    }
    using namespace Utilities;
}
using namespace Common;
_NS_END_