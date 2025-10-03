/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  ////////////////////
  // Convenience
  ////////////////////
  // A set of aliases for commonly used types.
  using str = std::string;
  using str_view = std::string_view;
  template <class T> using s_ptr = std::shared_ptr<T>;
  template <class T> using vec = std::vector<T>;
  template <class T> using func = std::function<T>;

  // Constants that may be used throughout the project.
  static constexpr int k_one_second_millis{
      1000}; ///< Number of milliseconds in one second.

  // Singleton functions
  /**
   * \brief Returns a singleton of an object of type T, in the
   *        form of a SharedPtr.
   *
   * \tparam T Type to get singleton for.
   * \return The singleton object as a SharedPtr.
   */
  template <class T> s_ptr<T> get_singleton_ptr() {
    // Create singleton instance only once.
    static s_ptr<T> inst = std::make_shared<T>();
    return inst;
  }

  /**
   * \brief Returns a singleton of an object of type T, in the
   *        form of a reference.
   *
   * \tparam T Type to get singleton for.
   * \return The singleton object as a reference.
   */
  template <class T> T &get_singleton() {
    // Use the SharedPtr singleton function to obtain
    // the singleton, but return a reference to it.
    return *get_singleton_ptr<T>();
  }

  // Convenience classes
  /**
   * \brief Class used for SharedPtrs of SDL objects,
   *        which handles automaticallyfreeing up resources at object deletion.
   */
  class sdl_deleter {
   public:
    /**
     * \brief Operator overloading for SDL_Window objects.
     *
     * \param win SDL window pointer to free resources for.
     */
    void operator()(SDL_Window *win) const;

    /**
     * \brief Operator overloading for SDL_Renderer objects.
     *
     * \param rend SDL renderer pointer to free resources for.
     */
    void operator()(SDL_Renderer *rend) const;

    /**
     * \brief Operator overloading for SDL_Surface objects.
     *
     * \param surf SDL surface pointer to free resources for.
     */
    void operator()(SDL_Surface *surf) const;

    /**
     * \brief Operator overloading for SDL_Texture objects.
     *
     * \param tex SDL texture pointer to free resources for.
     */
    void operator()(SDL_Texture *tex) const;

    /**
     * \brief Operator overloading for TTF_Font objects.
     *
     * \param font SDL font pointer to free resources for.
     */
    void operator()(TTF_Font *font) const;
  };

  ////////////////////
  // Matter
  ////////////////////
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

  ////////////////////
  // Utils
  ////////////////////
  // Canvas util functions
  size get_canvas_size();

  float calculate_aspect_ratio();

  float convert_width_to_height(float w);

  float convert_height_to_width(float h);

  // File path util functions
  str get_file_extension(str_view path);

  str get_file_name_no_extension(str_view path);

  // Mouse util functions
  point_f get_normalized_mouse_position();

  // Numbers util functions
  float invert_movement_speed(float num);

  int normalize(int val);

  float ceil(float num, float k);

  // Randomization util functions
  void randomize();

  int random_int(int upper_lim);

  // String util functions
  str replace(str_view text, char repl, char repl_with);

  // Time util functions
  const auto get_ticks{SDL_GetTicks};

  // Hash util functions
  /**
   * \brief Compute hash code from a given input text, which
   *        gets computed the same every game start.
   *
   * \param text Text to compute hash code for.
   * \return Computed hash code.
   */
  int hash(str_view text);

  // Print util functions
  /**
   * \brief Print out a string of text, without a following line break.
   *
   * \param text Text to print.
   */
  void print(str_view text);

  /**
   * \brief Print out a string of text, with an added line break at the end.
   *
   * \param text Text to print.
   */
  void print_line(str_view text);

  // Cast util functions
  int c_int(auto val) { return static_cast<int>(val); }

  float c_float(auto val) { return static_cast<float>(val); }

  Uint8 c_uint8(auto val) { return static_cast<Uint8>(val); }
}