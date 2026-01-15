/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <unordered_map>
#include <GL/glew.h>
#include <GL/gl.h>
#include "ModelRenderingOperation.hpp"
#include "ForradiaEngine/Rendering/Base/RendererBase.hpp"

namespace ForradiaEngine
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
         *  @param elevationHeight The height of the elevation.
         *  @param levitationHeight The height of the levitation.
         */
        auto drawModel(int modelNameHash, float xPos, float yPos, float elevations,
                       float modelScaling = 1.0F, float modelRotation = 0.0F, float elevationHeight = k_defaultElevationHeight,
                       float levitationHeight = 0.0F) -> void;

        /**
         *  Sets up the state for the model renderer.
         */
        auto setupState() const -> void;

        /**
         *  Restores the state for the model renderer.
         */
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

        constexpr static float k_globalModelScaling{0.5F};
        constexpr static float k_defaultElevationHeight{0.15F};
        std::unordered_map<int, ModelRenderingOperation> m_operationsCache{};
        GLint m_layoutLocationProjectionMatrix{};
        GLint m_layoutLocationViewMatrix{};
        GLint m_layoutLocationModelMatrix{};
    };
}
