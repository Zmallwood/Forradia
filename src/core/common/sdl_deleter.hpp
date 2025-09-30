/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia {
  /**
   * \brief Class used for SharedPtrs of SDL objects,
   *        which handles automaticallyfreeing up resources at object deletion.
   */
  class SDLDeleter {
  public:
    /**
     * \brief Operator overloading for SDL_Window objects.
     *
     * \param window SDL window pointer to free resources for.
     */
    void operator()(SDL_Window *window) const;

    /**
     * \brief Operator overloading for SDL_Renderer objects.
     *
     * \param window SDL renderer pointer to free resources for.
     */
    void operator()(SDL_Renderer *renderer) const;

    /**
     * \brief Operator overloading for SDL_Surface objects.
     *
     * \param window SDL surface pointer to free resources for.
     */
    void operator()(SDL_Surface *surface) const;

    /**
     * \brief Operator overloading for SDL_Texture objects.
     *
     * \param window SDL texture pointer to free resources for.
     */
    void operator()(SDL_Texture *texture) const;

    /**
     * \brief Operator overloading for TTF_Font objects.
     *
     * \param window SDL font pointer to free resources for.
     */
    void operator()(TTF_Font *font) const;
  };
}
