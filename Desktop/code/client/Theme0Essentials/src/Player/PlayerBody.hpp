//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "PlayerBodyPartTypes.hpp"

namespace Forradia::Theme0::GameplayCore
{
    class PlayerBodyPart;

    class PlayerBody
    {
      public:
        PlayerBody()
        {
            Initialize();
        }

        SharedPtr<PlayerBodyPart> GetBodyPartPtr(PlayerBodyPartTypes bodyPartType);

      private:
        void Initialize();

        std::map<PlayerBodyPartTypes, SharedPtr<PlayerBodyPart>> m_bodyParts;
    };
}