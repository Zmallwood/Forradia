//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

namespace Forradia::Theme0
{
    ///
    /// Class for storing object properties.
    ///
    class ObjectIndexEntry
    {
      public:
        float modelScaling{1.0f}; ///< The scaling factor for the object model.
        bool ignoreIndividualModelScaling{
            false}; ///< Whether to ignore the individual model scaling.
    };
}