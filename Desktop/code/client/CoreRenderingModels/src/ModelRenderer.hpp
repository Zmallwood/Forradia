//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "RendererBase.hpp"

#include "ModelRenderingOperation.hpp"

namespace AAK
{
    namespace Forradia
    {
        ///
        /// Renders models from the model bank in 3D space.
        ///
        class ModelRenderer : public RendererBase
        {
          public:
            ///
            /// Destructor that cleans up the renderer.
            ///
            ~ModelRenderer()
            {
                // Clean up the renderer.

                this->Cleanup();
            }

            ///
            /// Draws a model in 3D space.
            ///
            /// @param modelNameHash The hash of the model to
            /// draw.
            /// @param x The x coordinate of the model.
            /// @param y The y coordinate of the model.
            /// @param elevations The elevations of the tile where the model is located.
            ///
            void DrawModel(int modelNameHash, float x, float y, float elevations,
                           float modelScaling = 1.0f);

          protected:
            ///
            /// Gets the vertex shader source.
            ///
            String GetVSSource() const override;

            ///
            /// Gets the fragment shader source.
            ///
            String GetFSSource() const override;

            ///
            /// Additional initialization for this derived class.
            ///
            void InitializeDerived() override;

            ///
            /// Sets up the attribute layout.
            ///
            void SetupAttributeLayout() const override;

          private:
            ///
            /// Cleans up the renderer.
            ///
            void Cleanup();

            ///
            /// Sets up the state for the renderer.
            ///
            void SetupState() const;

            ///
            /// Restores the state for the renderer.
            ///
            void RestoreState() const;

            ///
            /// Checks if the drawing operation is cached.
            ///
            /// @param modelNameHash The hash of the model to check.
            /// @return True if the drawing operation is cached, false otherwise.
            ///
            bool DrawingOperationIsCached(int modelNameHash) const;

            static constexpr float k_globalModelScaling{0.5f}; ///< Global scale factor for models.

            std::map<int,
                     ModelRenderingOperation> m_operationsCache; ///< The operations cache.

            GLint m_layoutLocationProjectionMatrix; /// < The location of the projection matrix.

            GLint m_layoutLocationViewMatrix; /// < The location of the view matrix.

            GLint m_layoutLocationModelMatrix; /// < The location of the model matrix.
        };
    }
}