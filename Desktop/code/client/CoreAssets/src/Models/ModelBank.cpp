/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "ModelBank.hpp"
#include "Construction/Model.hpp"
#include "FilePathUtilities.hpp"
#include "Hash.hpp"
#include "StringUtilities.hpp"
#include <SDL2/SDL.h>
#include <filesystem>

namespace Forradia {
  auto ModelBank::Initialize() -> void {
    ModelBank::LoadModels();
  }

  auto ModelBank::LoadModels() -> void {
    auto basePath{std::string(SDL_GetBasePath())};
    auto imagesPath{basePath + k_relativeModelsPath};

    if (false == std::filesystem::exists(imagesPath))
      return;

    std::filesystem::recursive_directory_iterator rdi{imagesPath};

    // Iterate through the directory using the rdi.
    for (const auto &file : rdi) {
      auto filePath{Replace(file.path().string(), '\\', '/')};

      if (GetFileExtension(filePath) == "obj" || GetFileExtension(filePath) == "dae") {
        auto fileName{GetFileNameNoExtension(filePath)};
        auto hash{Forradia::Hash(fileName)};
        auto model{ModelBank::LoadSingleModel(filePath)};
        m_models.insert({hash, model});
      }
    }
  }

  auto ModelBank::GetModel(int modelNameHash) -> std::shared_ptr<Model> {
    if (m_models.contains(modelNameHash))
      return m_models.at(modelNameHash);
    return nullptr;
  }

  auto ModelBank::LoadSingleModel(std::string_view filePath) -> std::shared_ptr<Model> {
    // Load the model from the file at the path.
    auto modelResult{std::make_shared<Model>(filePath)};
    return modelResult;
  }
}
