//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "ModelBank.hpp"
#include "Construction/Model.hpp"

namespace Forradia {
    void ModelBank::Initialize() {
        this->LoadModels();
    }

    void ModelBank::LoadModels() {
        auto basePath{String(SDL_GetBasePath())};
        auto imagesPath{basePath + k_relativeModelsPath.data()};

        if (false == std::filesystem::exists(imagesPath)) {
            return;
        }

        std::filesystem::recursive_directory_iterator rdi{imagesPath};

        // Iterate through the directory using the rdi.
        for (auto it : rdi) {
            auto filePath{Replace(it.path().string(), '\\', '/')};

            if (GetFileExtension(filePath) == "obj") {
                auto fileName{GetFileNameNoExtension(filePath)};
                auto hash{Forradia::Hash(fileName)};
                auto model{this->LoadSingleModel(filePath)};
                m_models.insert({hash, model});
            }
        }
    }

    SharedPtr<Model> ModelBank::GetModel(int modelNameHash) const {
        if (m_models.contains(modelNameHash)) {
            return m_models.at(modelNameHash);
        }
        return nullptr;
    }

    SharedPtr<Model> ModelBank::LoadSingleModel(StringView filePath) const {
        // Load the model from the file at the path.
        auto modelResult{std::make_shared<Model>(filePath)};
        return modelResult;
    }
}