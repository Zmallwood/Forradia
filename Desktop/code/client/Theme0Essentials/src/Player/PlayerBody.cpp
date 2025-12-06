//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "PlayerBody.hpp"
#include "PlayerBodyPart.hpp"

namespace Forradia::Theme0::GameplayCore
{
    void PlayerBody::Initialize()
    {
        // Add all body parts.

        m_bodyParts.insert({PlayerBodyPartTypes::OverallBody, std::make_shared<PlayerBodyPart>()});

        m_bodyParts.insert({PlayerBodyPartTypes::RightArm, std::make_shared<PlayerBodyPart>()});

        m_bodyParts.insert({PlayerBodyPartTypes::LeftArm, std::make_shared<PlayerBodyPart>()});

        m_bodyParts.insert({PlayerBodyPartTypes::Legs, std::make_shared<PlayerBodyPart>()});
    }

    SharedPtr<PlayerBodyPart> PlayerBody::GetBodyPartPtr(PlayerBodyPartTypes bodyPartType)
    {
        // Check if body part exists.

        if (!m_bodyParts.contains(bodyPartType))
        {
            // The body part does not exist.

            return nullptr;
        }

        // Return pointer to body part.

        return m_bodyParts.at(bodyPartType);
    }
}