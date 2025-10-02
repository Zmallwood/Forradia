/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  /**
   * \brief Returns a singleton of an object of type T, in the
   *        form of a SharedPtr.
   *
   * \tparam T Type to get singleton for.
   * \return The singleton object as a SharedPtr.
   */
  template <class T> s_ptr<T> get_singleton_ptr() {
    // Create singleton instance only once.
    static s_ptr<T> instance = std::make_shared<T>();
    return instance;
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
}
