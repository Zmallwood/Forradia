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
  SharedPtr<Model> GetModel(int modelNameHash) const;

 private:
  void Initialize();

  void LoadModels();

  SharedPtr<Model> LoadSingleModel(StringView filePath) const;

  inline static const String k_relativeModelsPath{"./Resources/Models/"};
  std::map<int, SharedPtr<Model>> m_models;
};
}