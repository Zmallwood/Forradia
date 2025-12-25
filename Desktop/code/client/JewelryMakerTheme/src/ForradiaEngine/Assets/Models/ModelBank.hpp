/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include <memory>
    #include <unordered_map>
// clang-format on

namespace ForradiaEngine
{
    class Model;

    /**
     *  Loads, stores and provides models.
     */
    class ModelBank
    {
      public:
        static auto instance() -> ModelBank &
        {
            static ModelBank instance;
            return instance;
        }

        ModelBank(const ModelBank &) = delete;

        auto operator=(const ModelBank &) -> ModelBank & = delete;

        /**
         *  Constructor.
         */
        ModelBank()
        {
            ModelBank::initialize();
        }

        /**
         *  Get a model by name hash.
         *
         *  @param modelNameHash The hash of the model name.
         *  @return The model.
         */
        // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
        [[nodiscard]] auto getModel(int modelNameHash) const -> std::shared_ptr<Model>;

      private:
        static auto initialize() -> void;

        static auto loadModels() -> void;

        static auto loadSingleModel(std::string_view filePath) -> std::shared_ptr<Model>;

        inline static const std::string k_relativeModelsPath{"./Resources/Models/"};
        inline static std::unordered_map<int, std::shared_ptr<Model>> m_models{};
    };
}
