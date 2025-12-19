/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

#include "Aliases.hpp"
#include <map>

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
      ModelBank::Initialize();
    }

    /**
     * Get a model by name hash.
     *
     * @param modelNameHash The hash of the model name.
     * @return The model.
     */
    static auto GetModel(int modelNameHash) -> SharedPtr<Model>;

   private:
    static auto Initialize() -> void;

    static auto LoadModels() -> void;

    static auto LoadSingleModel(StringView filePath) -> SharedPtr<Model>;

    inline static const String k_relativeModelsPath{"./Resources/Models/"};
    inline static std::map<int, SharedPtr<Model>> m_models;
  };
}
