/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "ModelRenderingOperation.hpp"
#include "Rendering/Base/RendererBase.hpp"
#include <unordered_map>
// clang-format off
#include <GL/glew.h>
#include <GL/gl.h>
// clang-format on

namespace Forradia
{
    /**
     *  This renderer is used to render models from the model bank in 3D space.
     */
    class ModelRenderer : public RendererBase
    {
      public:
        static auto instance() -> ModelRenderer &
        {
            static ModelRenderer instance;
            return instance;
        }

        ModelRenderer(const ModelRenderer &) = delete;

        auto operator=(const ModelRenderer &) -> ModelRenderer & = delete;

        ModelRenderer() = default;

        /**
         *  Destructor that cleans up the renderer.
         */
        ~ModelRenderer() override
        {
            // Clean up the renderer.
            this->cleanup();
        }

        /**
         *  Draws a model in 3D space.
         *
         *  @param modelNameHash The hash of the model to draw.
         *  @param xPos The x coordinate of the model.
         *  @param yPos The y coordinate of the model.
         *  @param elevations The elevations of the tile where the model is located.
         *  @param modelScaling The scaling of the model.
         */
        auto drawModel(int modelNameHash, float xPos, float yPos, float elevations,
                       float modelScaling = 1.0F) -> void;

        auto setupState() const -> void;

        static auto restoreState() -> void;

      protected:
        /**
         *  Gets the vertex shader source.
         *
         *  @return The vertex shader source.
         */
        [[nodiscard]] auto getVSSource() const -> std::string override;

        /**
         *  Gets the fragment shader source.
         *
         *  @return The fragment shader source.
         */
        [[nodiscard]] auto getFSSource() const -> std::string override;

        /**
         *  Additional initialization for this derived class.
         */
        auto initializeDerived() -> void override;

        /**
         *  Sets up the attribute layout.
         */
        auto setupAttributeLayout() const -> void override;

      private:
        auto cleanup() -> void;

        [[nodiscard]] auto drawingOperationIsCached(int modelNameHash) const -> bool;

        static constexpr float k_globalModelScaling{0.5F};
        std::unordered_map<int, ModelRenderingOperation> m_operationsCache{};
        GLint m_layoutLocationProjectionMatrix{};
        GLint m_layoutLocationViewMatrix{};
        GLint m_layoutLocationModelMatrix{};
    };
}
