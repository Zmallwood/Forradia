//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    class Model;

    class ModelBank
    {
      public:
        ModelBank()
        {
            Initialize();
        }

        SharedPtr<Model> GetModel(int modelNameHash) const;

      private:
        void Initialize();

        SharedPtr<Model>
        LoadSingleModel(StringView filePath);

        inline static const String k_relativeModelsPath{
            "./Resources/Models/"};

        std::map<int, SharedPtr<Model>> m_models;
    };
}