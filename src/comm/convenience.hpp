/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
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
}