//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "ModelBank.hpp"

#include "Construction/Model.hpp"

namespace Forradia
{
    void ModelBank::Initialize()
    {
        // Load models from the file system.

        this->LoadModels();
    }

    void ModelBank::LoadModels()
    {
        // Take base path from SDL.

        auto basePath{String(SDL_GetBasePath())};

        // Add relative path to base path.

        auto imagesPath{basePath +
                        k_relativeModelsPath.data()};

        // Ensure the path exists to continue.

        if (false == std::filesystem::exists(imagesPath))
        {
            return;
        }

        // Create a recursive directory iterator for the
        // path.

        std::filesystem::recursive_directory_iterator rdi{
            imagesPath};

        // Iterate through the directory using the rdi.

        for (auto it : rdi)
        {
            // Replace backslashes with forward slashes.

            auto filePath{
                Replace(it.path().string(), '\\', '/')};

            // If the file is an OBJ file.

            if (GetFileExtension(filePath) == "obj")
            {
                // Get the file name.

                auto fileName{
                    GetFileNameNoExtension(filePath)};

                // Get the hash of the file name.

                auto hash{Forradia::Hash(fileName)};

                // Load the model from the file at the path.

                auto model{this->LoadSingleModel(filePath)};

                // Insert the model into the map.

                m_models.insert({hash, model});
            }
        }
    }

    SharedPtr<Model>
    ModelBank::GetModel(int modelNameHash) const
    {
        // If the model is in the map.

        if (m_models.contains(modelNameHash))
        {
            // Return it.

            return m_models.at(modelNameHash);
        }

        // If the model is not in the map.

        return nullptr;
    }

    SharedPtr<Model>
    ModelBank::LoadSingleModel(StringView filePath)
    {
        // Load the model from the file at the path.

        auto modelResult{std::make_shared<Model>(filePath)};

        // Return the model.

        return modelResult;
    }
}