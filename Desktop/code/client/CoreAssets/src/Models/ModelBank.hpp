//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#pragma once

namespace Forradia
{
    class Model;

    /// Loads, stores and provides models.
    class ModelBank
    {
      public:
        /// Default constructor.
        ModelBank()
        {
            this->Initialize();
        }

        /// Get a model by name hash.
        ///
        /// @param modelNameHash The hash of the model name.
        /// @return The model.
        SharedPtr<Model> GetModel(int modelNameHash) const;

      private:
        /// Initializes the model bank.
        void Initialize();

        /// Loads all models from the file system.
        void LoadModels();

        /// Loads a single model from the file system.
        ///
        /// @param filePath The path to the model file.
        /// @return The loaded model.
        SharedPtr<Model> LoadSingleModel(StringView filePath) const;

        inline static const String k_relativeModelsPath{
            "./Resources/Models/"}; ///< Relative path to models.

        std::map<int, SharedPtr<Model>> m_models; ///< Models.
    };
}