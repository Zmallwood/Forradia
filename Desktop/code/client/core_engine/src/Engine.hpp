//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    class Engine
    {
      public:
        void Initialize(StringView gameWindowTitle, Color clearColor) const;

        void Run();

        void Stop();

      private:
        void HandleEvents();

        bool m_running{true};
    };
}