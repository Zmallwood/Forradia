//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUI.hpp"

#include "Rendering.hpp"

namespace Forradia
{
    class Engine
    {
      public:
        class Renderers : public RenderersCollection
        {
          public:
            using RenderersCollection::FontSizes;

            using RenderersCollection::GroundRenderer;

            using RenderersCollection::Image2DRenderer;

            using RenderersCollection::ModelRenderer;

            using RenderersCollection::TextRenderer;
        };

        void Initialize(StringView gameWindowTitle,
                        Color clearColor) const;

        void Run();

        void Stop();

      private:
        void PollEvents();

        bool m_running{true};
    };
}