/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <memory>

namespace Forradia
{
    class ShaderProgram;

    /**
     * Base class for all renderers.
     */
    class RendererBase
    {
      public:
        virtual ~RendererBase() = default;

        /**
         * Initialize the renderer with its shader program.
         */
        auto Initialize() -> void;

        /**
         * Get the shader program.
         *
         * @return The shader program.
         */
        [[nodiscard]] auto GetShaderProgram() const
        {
            return m_shaderProgram;
        }

      protected:
        /**
         * Get the vertex shader source code.
         *
         * @return The vertex shader source code.
         */
        [[nodiscard]] virtual auto GetVSSource() const -> std::string = 0;

        /**
         * Get the fragment shader source code.
         *
         * @return The fragment shader source code.
         */
        [[nodiscard]] virtual auto GetFSSource() const -> std::string = 0;

        /**
         * Can be used to do additional initialization implemented in deriving class.
         */
        virtual auto InitializeDerived() -> void
        {
        }

        /**
         * Set up the attribute layout.
         */
        virtual auto SetupAttributeLayout() const -> void = 0;

      private:
        std::shared_ptr<ShaderProgram> m_shaderProgram{};
    };
}
