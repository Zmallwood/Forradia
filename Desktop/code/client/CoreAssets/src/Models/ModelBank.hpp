/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <memory>
#include <unordered_map>

namespace Forradia {
    class Model;

    /**
     * Loads, stores and provides models.
     */
    class ModelBank {
      public:
        static auto Instance() -> ModelBank & {
            static ModelBank instance;
            return instance;
        }

        // Delete copy/move
        ModelBank(const ModelBank &) = delete;

        auto operator=(const ModelBank &) -> ModelBank & = delete;

        /**
         * Constructor.
         */
        ModelBank() {
            ModelBank::Initialize();
        }

        /**
         * Get a model by name hash.
         *
         * @param modelNameHash The hash of the model name.
         * @return The model.
         */
        auto GetModel(int modelNameHash) const -> std::shared_ptr<Model>;

      private:
        static auto Initialize() -> void;

        static auto LoadModels() -> void;

        static auto LoadSingleModel(std::string_view filePath) -> std::shared_ptr<Model>;

        inline static const std::string k_relativeModelsPath{"./Resources/Models/"};
        inline static std::unordered_map<int, std::shared_ptr<Model>> m_models;
    };
}
