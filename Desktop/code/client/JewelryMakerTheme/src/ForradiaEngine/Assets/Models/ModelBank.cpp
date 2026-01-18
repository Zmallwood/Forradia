/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ModelBank.hpp"
#include <filesystem>
#include <SDL2/SDL.h>
#include "Model.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"
#include "ForradiaEngine/Common/General.hpp"

namespace ForradiaEngine
{
    auto ModelBank::initialize() -> void
    {
        ModelBank::loadModels();
    }

    auto ModelBank::loadModels() -> void
    {
        auto basePath{std::string(SDL_GetBasePath())};
        auto imagesPath{basePath + k_relativeModelsPath};

        If(false == std::filesystem::exists(imagesPath))
        {
            return;
        }

        std::filesystem::recursive_directory_iterator rdi{imagesPath};

        // Iterate through the directory using the rdi.
        for (const auto &file : rdi)
        {
            auto filePath{replace(file.path().string(), '\\', '/')};

            If(getFileExtension(filePath) == "obj" || getFileExtension(filePath) == "dae")
            {
                auto fileName{getFileNameNoExtension(filePath)};
                auto hash{ForradiaEngine::hash(fileName)};
                auto model{ModelBank::loadSingleModel(filePath)};

                m_models.insert({hash, model});
            }
        }
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto ModelBank::getModel(int modelNameHash) const -> std::shared_ptr<Model>
    {
        If(m_models.contains(modelNameHash))
        {
            return m_models.at(modelNameHash);
        }

        return nullptr;
    }

    auto ModelBank::loadSingleModel(std::string_view filePath) -> std::shared_ptr<Model>
    {
        // Load the model from the file at the path.
        auto modelResult{std::make_shared<Model>(filePath)};

        return modelResult;
    }
}
