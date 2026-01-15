/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <memory>

using SDL_GLContext = void *;

namespace ForradiaEngine
{
    /**
     *  Sets up the OpenGL context and the OpenGL functions.
     */
    class GLDevice
    {
      public:
        static auto instance() -> GLDevice &
        {
            static GLDevice instance;
            return instance;
        }

        GLDevice(const GLDevice &) = delete;

        auto operator=(const GLDevice &) -> GLDevice & = delete;

        GLDevice() = default;

        /**
         *  Default destructor.
         */
        ~GLDevice();

        /**
         *  Initializes this device by setting up the GL functionality.
         */
        auto initialize() -> void;

      private:
        auto setupGL() -> void;

        std::shared_ptr<SDL_GLContext> m_context{};
    };
}
