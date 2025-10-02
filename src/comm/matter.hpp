/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  /**
   * \brief Point in 2D space, using dimensions of int type.
   */
  class point {
  public:
    /**
     * \brief Equality operator between two Points.
     *
     * \param p Other Point to check equality against.
     * \return True if the two points are equal, otherwise false.
     */
    bool operator==(const point &p) const;

    int x{0};
    int y{0};
  };

  /**
   * \brief Point in 2D space using dimensions of float type.
   */
  class point_f {
  public:
    /**
     * \brief Summing operator for the two points.
     *
     * \param p The other PointF to add to this point.
     * \return The resulting PointF with the dimensions added separately.
     */
    point_f operator+(const point_f &p) const;

    /**
     * \brief Subtraction operator for the two points.
     *
     * \param p The other PointF to subtract from this point.
     * \return The resulting PointF with the dimensions subtracted separetely.
     */
    point_f operator-(const point_f &p) const;

    float x{0.0f}; ///< The x dimension.
    float y{0.0f}; ///< The y dimension.
  };

  /**
   * \brief Size in 2D space, with the dimensions as int values.
   */
  class size {
  public:
    int w{0}; ///< Width.
    int h{0}; /// Height.
  };

  /**
   * \brief Size in 2D space with dimensions of float values.
   */
  class size_f {
  public:
    float w{0.0f}; ///< Width.
    float h{0.0f}; ///< Height.
  };

  /**
   * \brief A rectangle in 2D space using dimensions of float type.
   */
  class rect_f {
  public:
    /**
     * \brief Check if this rectangle contains a certian point.
     *
     * \param p Point to check if it is contained in this rectangle.
     * \return True if the Point is within this rectangle, otherwise false.
     */
    bool contains(point_f p);

    /**
     * \brief Returns only the position of this rectangle.
     *
     * \return The position.
     */
    point_f get_position() const;

    /**
     * \brief Adds an offset to this rectangle, with the dimensions altered
     * separately.
     *
     * \param offs The offset to add.
     */
    void offset(point_f offs);

    float x{0.0f}; ///< The x coordinate.
    float y{0.0f}; ///< The y coordinate.
    float w{0.0f}; ///< The width, in the x dimension.
    float h{0.0f}; ///< The height, in the y dimension.
  };

  /**
   * \brief A RGBA color with components defined with float values.
   */
  class color {
  public:
    /**
     * \brief Convert this color to a corresponding SDL_Color object.
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
   * \brief Contains a palette of colors.
   */
  namespace colors {
    constexpr color black{0.0f, 0.0f, 0.0f, 1.0f}; ///< Black color.

    constexpr color wheat{1.0f, 1.0f, 0.65f, 1.0f}; ///< Wheat color.

    constexpr color wheat_transp{1.0f, 1.0f, 0.65f,
                                 0.7f}; ///< Transparent wheat color.

    constexpr color yellow{1.0f, 1.0f, 0.0f, 1.0f}; ///< Yellow color.

    constexpr color yellow_transp{1.0f, 1.0f, 0.0f,
                                  0.7f}; ///< Transparent yellow color.
  }
}
