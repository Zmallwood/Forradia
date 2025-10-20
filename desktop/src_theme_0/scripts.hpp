/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

_NS_START_
namespace Scripting
{
    class script_engine
    {
      public:
        void init();

        void load_scripts();
    };
}
using namespace Scripting;
_NS_END_