//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "BodyPartTypes.hpp"

#include "BodyPart.hpp"

namespace Forradia::Theme0::GameplayCore
{
    class PlayerBody
    {
      public:
        PlayerBody()
        {
            Initialize();
        }

        BodyPart *
        GetBodyPartPtr(BodyPartTypes bodyPartType);

      private:
        void Initialize();

        std::map<BodyPartTypes, BodyPart> m_bodyParts;
    };
}