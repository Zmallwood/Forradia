//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    class MapEditor
    {
      public:
        void Run();

        void PollEvents();

        bool m_running{true};
    };
}