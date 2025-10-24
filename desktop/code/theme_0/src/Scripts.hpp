//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    namespace Theme0
    {
        namespace Scripting
        {
            class ScriptEngine
            {
              public:
                void Initialize();

                void LoadScripts();
            };
        }
        using namespace Scripting;
    }
}