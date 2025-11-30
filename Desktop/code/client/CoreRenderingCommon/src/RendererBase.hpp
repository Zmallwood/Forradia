//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace AAK
{
    namespace Forradia
    {
        class ShaderProgram;

        ///
        /// Base class for all renderers.
        ///
        class RendererBase
        {
          public:
            ///
            /// Initialize the renderer with its shader program.
            ///
            void Initialize();

          protected:
            ///
            /// Gets the vertex shader source code. This is used by Initialize() to create the
            /// shader program.
            ///
            /// @return The vertex shader source code.
            ///
            virtual String GetVSSource() const = 0;

            ///
            /// Gets the fragment shader source code. This is used by Initialize() to create the
            /// shader program.
            ///
            /// @return The fragment shader source code.
            ///
            virtual String GetFSSource() const = 0;

            ///
            /// Can be used to do additional initialization implemented in deriving class.
            ///
            virtual void InitializeDerived()
            {
            }

            ///
            /// Sets up the attribute layout.
            ///
            virtual void SetupAttributeLayout() const = 0;

            ///
            /// Gets the shader program.
            ///
            /// @return
            ///
            auto GetShaderProgram() const
            {
                return m_shaderProgram;
            }

          private:
            SharedPtr<ShaderProgram> m_shaderProgram; ///< The shader program.
        };
    }
}