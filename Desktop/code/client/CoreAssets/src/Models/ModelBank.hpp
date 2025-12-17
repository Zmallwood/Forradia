/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
class Model;

/**
 * Loads, stores and provides models.
 */
class ModelBank {
 public:
  /**
   * Constructor.
   */
  ModelBank() {
    this->Initialize();
  }

  /**
   * Get a model by name hash.
   *
   * @param modelNameHash The hash of the model name.
   * @return The model.
   */
  auto GetModel(int modelNameHash) const -> SharedPtr<Model>;

 private:
  auto Initialize() -> void;

  auto LoadModels() -> void;

  auto LoadSingleModel(StringView filePath) const -> SharedPtr<Model>;

  inline static const String k_relativeModelsPath{"./Resources/Models/"};
  std::map<int, SharedPtr<Model>> m_models;
};
}
