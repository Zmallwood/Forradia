//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "PlayerBody.hpp"

namespace Forradia::Theme0::GameplayCore
{
    void PlayerBody::Initialize()
    {
        m_bodyParts.insert({BodyPartTypes::OverallBody, BodyPart()});

        m_bodyParts.insert({BodyPartTypes::RightArm, BodyPart()});

        m_bodyParts.insert({BodyPartTypes::LeftArm, BodyPart()});

        m_bodyParts.insert({BodyPartTypes::Legs, BodyPart()});
    }

    BodyPart *PlayerBody::GetBodyPartPtr(BodyPartTypes bodyPartType)
    {
        if (m_bodyParts.contains(bodyPartType))
        {
            return &m_bodyParts.at(bodyPartType);
        }

        return nullptr;
    }
}