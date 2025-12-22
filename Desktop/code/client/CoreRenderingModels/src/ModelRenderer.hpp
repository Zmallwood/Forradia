/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "ModelRenderingOperation.hpp"
#include "RendererBase.hpp"
#include <unordered_map>
// clang-format off
#include <GL/glew.h>
#include <GL/gl.h>
// clang-format on

namespace Forradia {
    /**
     * This renderer is used to render models from the model bank in 3D space.
     */
    class ModelRenderer : public RendererBase {
      public:
        static auto Instance() -> ModelRenderer & {
            static ModelRenderer instance;
            return instance;
        }

        // Delete copy/move
        ModelRenderer(const ModelRenderer &) = delete;

        auto operator=(const ModelRenderer &) -> ModelRenderer & = delete;

        ModelRenderer() = default;

        /**
         * Destructor that cleans up the renderer.
         */
        ~ModelRenderer() {
            // Clean up the renderer.
            this->Cleanup();
        }

        /**
         * Draws a model in 3D space.
         *
         * @param modelNameHash The hash of the model to draw.
         * @param xPos The x coordinate of the model.
         * @param yPos The y coordinate of the model.
         * @param elevations The elevations of the tile where the model is located.
         * @param modelScaling The scaling of the model.
         */
        auto DrawModel(int modelNameHash, float xPos, float yPos, float elevations,
                       float modelScaling = 1.0F) -> void;

      protected:
        /**
         * Gets the vertex shader source.
         *
         * @return The vertex shader source.
         */
        [[nodiscard]] auto GetVSSource() const -> std::string override;

        /**
         * Gets the fragment shader source.
         *
         * @return The fragment shader source.
         */
        [[nodiscard]] auto GetFSSource() const -> std::string override;

        /**
         * Additional initialization for this derived class.
         */
        auto InitializeDerived() -> void override;

        /**
         * Sets up the attribute layout.
         */
        auto SetupAttributeLayout() const -> void override;

      private:
        auto Cleanup() -> void;

        auto SetupState() const -> void;

        static auto RestoreState() -> void;

        [[nodiscard]] auto DrawingOperationIsCached(int modelNameHash) const -> bool;

        static constexpr float k_globalModelScaling{0.5F};
        std::unordered_map<int, ModelRenderingOperation> m_operationsCache{};
        GLint m_layoutLocationProjectionMatrix{};
        GLint m_layoutLocationViewMatrix{};
        GLint m_layoutLocationModelMatrix{};
    };
}
