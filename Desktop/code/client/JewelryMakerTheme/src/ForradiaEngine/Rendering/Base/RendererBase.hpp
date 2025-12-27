/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <memory>

namespace ForradiaEngine
{
    class ShaderProgram;

    /**
     *  Base class for all renderers.
     */
    class RendererBase
    {
      public:
        virtual ~RendererBase() = default;

        /**
         *  Initialize the renderer with its shader program.
         */
        auto initialize() -> void;

        /**
         *  Get the shader program.
         *
         *  @return The shader program.
         */
        [[nodiscard]] auto getShaderProgram() const
        {
            return m_shaderProgram;
        }

      protected:
        /**
         *  Get the vertex shader source code.
         *
         *  @return The vertex shader source code.
         */
        [[nodiscard]] virtual auto getVSSource() const -> std::string = 0;

        /**
         *  Get the fragment shader source code.
         *
         *  @return The fragment shader source code.
         */
        [[nodiscard]] virtual auto getFSSource() const -> std::string = 0;

        /**
         *  Can be used to do additional initialization implemented in deriving class.
         */
        virtual auto initializeDerived() -> void
        {
        }

        /**
         *  Set up the attribute layout.
         */
        virtual auto setupAttributeLayout() const -> void = 0;

      private:
        std::shared_ptr<ShaderProgram> m_shaderProgram{};
    };
}
