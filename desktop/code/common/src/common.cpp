/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "common.hpp"

_NS_START_
namespace Common
{
    void SDLDeleter::operator()(SDL_Window *win) const
    {
        // Free up resources from a SDL_Window object.
        SDL_DestroyWindow(win);
    }

    void SDLDeleter::operator()(SDL_Renderer *rend) const
    {
        // Free up resources from a SDL_Renderer object.
        SDL_DestroyRenderer(rend);
    }

    void SDLDeleter::operator()(SDL_Surface *surf) const
    {
        // Free up resources from a SDL_Surface object.
        SDL_FreeSurface(surf);
    }

    void SDLDeleter::operator()(SDL_Texture *tex) const
    {
        // Free up resources from a SDL_Texture object.
        SDL_DestroyTexture(tex);
    }

    void SDLDeleter::operator()(TTF_Font *font) const
    {
        // Free up resources from a TTF_Font object.
        TTF_CloseFont(font);
    }

    namespace Matter
    {
        bool Point::operator==(const Point &p) const
        {
            // Compare x and y dimensions.
            return p.x == x && p.y == y;
        }

        PointF PointF::operator+(const PointF &p) const
        {
            // Sum the dimensions of the two points.
            return {x + p.x, y + p.y};
        }

        PointF PointF::operator-(const PointF &p) const
        {
            // Subract the dimensions of the other point from this point.
            return {x - p.x, y - p.y};
        }

        bool RectF::Contains(PointF p)
        {
            // Create condition by checking against the boundaries of this
            // rectangle.
            return p.x >= x && p.y >= y && p.x < x + w && p.y < y + h;
        }

        PointF RectF::GetPosition() const
        {
            // Return only the coordinates.
            return {x, y};
        }

        void RectF::Offset(PointF offs)
        {
            // Add the offset to the dimensions separately.
            x += offs.x;
            y += offs.y;
        }
        namespace Coloring
        {
            SDL_Color Color::ToSDLColor() const
            {
                // Calculate individual color components.
                auto r_n{CUint8(r * 255)};
                auto g_n{CUint8(g * 255)};
                auto b_n{CUint8(b * 255)};
                auto a_n{CUint8(a * 255)};

                return {r_n, g_n, b_n, a_n};
            }
        }
    }
    namespace Utilities
    {
        namespace CanvasUtilities
        {
            // Canvas util functions
            Size GetCanvasSize(SharedPtr<SDL_Window> win)
            {
                Size canv_sz;
                // Get the size of the window.
                SDL_GetWindowSize(win.get(), &canv_sz.w, &canv_sz.h);

                return canv_sz;
            }

            float CalcAspectRatio(SharedPtr<SDL_Window> win)
            {
                auto canv_sz{GetCanvasSize(win)};
                // Calculate the aspect ratio.
                auto asp_rat{CFloat(canv_sz.w) / canv_sz.h};

                return asp_rat;
            }

            float ConvertWidthToHeight(float w, SharedPtr<SDL_Window> win)
            {
                // Calculate the height based on the width and the aspect ratio.
                return w * CalcAspectRatio(win);
            }

            float ConvertHeightToWidth(float h, SharedPtr<SDL_Window> win)
            {
                // Calculate the width based on the height and the aspect ratio.
                return h / CalcAspectRatio(win);
            }
        }
        namespace FilePathUtilities
        {
            // File path util functions
            String GetFileExtension(StringView path)
            {
                // Get the file extension.
                String ext{path.substr(path.find_last_of('.') + 1).data()};

                return ext;
            }

            String GetFileNameNoExtension(StringView path)
            {
                // Get the file name without the extension.
                auto name_with_ext{
                    String(path.substr(path.find_last_of('/') + 1))};

                return name_with_ext.substr(0, name_with_ext.find_last_of('.'));
            }
        }
        namespace MouseUtilities
        {
            // Mouse util functions
            PointF GetNormallizedMousePosition(SharedPtr<SDL_Window> win)
            {
                int x_px;
                int y_px;
                // Get the mouse position.
                SDL_GetMouseState(&x_px, &y_px);
                auto canv_sz{GetCanvasSize(win)};
                // Calculate the normalized mouse position.

                return {CFloat(x_px) / canv_sz.w, CFloat(y_px) / canv_sz.h};
            }
        }
        namespace NumbersUtilities
        {
            // Numbers util functions
            float InvertMovementSpeed(float num)
            {
                // Calculate the inverse of the movement speed.
                if (num)
                {
                    // If the movement speed is not zero, invert it and return.
                    return k_one_sec_millis / num;
                }
                else
                {
                    // If the movement speed is zero, avoid division by zero
                    // and return zero directly instead.
                    return 0.0f;
                }
            }

            int Normalize(int val)
            {
                auto abs_val{std::abs(val)};
                auto norm{0};

                // Calculate the normalized value.
                if (val)
                {
                    norm = val / abs_val;
                }

                return norm;
            }

            float Ceil(float num, float k)
            {
                // Calculate the ceiled value with k decimal places.
                auto p{std::pow(10.0, k)};

                return std::ceil(num * p) / p;
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

            int GetRandomInt(int upper_lim)
            {
                // Generate a random integer.
                return rand() % upper_lim;
            }
        }
        namespace StringUtilities
        {
            // String util functions
            String Replace(StringView text, char repl, char repl_with)
            {
                String res{text.data()};
                // Replace all instances of repl with repl_with.
                std::replace(res.begin(), res.end(), repl, repl_with);

                return res;
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