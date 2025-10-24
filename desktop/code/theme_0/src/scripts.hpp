/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

_NS_START_
#define _HIDE_FROM_OUTLINER_SCRIPTS_TOP_                                       \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_SCRIPTS_TOP_
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
_NS_END_