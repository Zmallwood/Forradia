//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Theme0Essentials.hpp"
#include "Core.hpp"
#include "SDLDevice.hpp"
#include "Theme0Properties.hpp"
#include "WorldStruct.hpp"

namespace Forradia
{
    namespace Theme0
    {
        float CalcTileSize()
        {
            auto aspectRatio{CalcAspectRatio(
                _<SDLDevice>().GetWindow())};
            return aspectRatio /
                   _<Theme0Properties>().k_numGridRows;
        }

        Size CalcGridSize()
        {
            auto tileSize{CalcTileSize()};

            auto aspectRatio{CalcAspectRatio(
                _<SDLDevice>().GetWindow())};

            auto numGridColumns{
                CInt(aspectRatio / tileSize) + 1};

            auto numGridRows{
                _<Theme0Properties>().k_numGridRows};

            return {numGridColumns, numGridRows};
        }

        namespace GameplayCore
        {
            void PlayerBody::Initialize()
            {
                m_bodyParts.insert(
                    {BodyPartTypes::OverallBody,
                     BodyPart()});

                m_bodyParts.insert(
                    {BodyPartTypes::RightArm, BodyPart()});

                m_bodyParts.insert(
                    {BodyPartTypes::LeftArm, BodyPart()});

                m_bodyParts.insert(
                    {BodyPartTypes::Legs, BodyPart()});
            }

            BodyPart *PlayerBody::GetBodyPartPtr(
                BodyPartTypes bodyPartType)
            {
                if (m_bodyParts.contains(bodyPartType))
                {
                    return &m_bodyParts.at(bodyPartType);
                }

                return nullptr;
            }

            void PlayerCharacter::Initialize()
            {
                this->MoveToSuitablePosition();
            }

            void PlayerCharacter::MoveToSuitablePosition()
            {
                auto worldArea{
                    _<World>().GetCurrentWorldArea()};

                auto size{worldArea->GetSize()};

                m_position = {size.width / 2,
                              size.height / 2};

                while (worldArea->GetTile(m_position)
                           ->GetGround() ==
                       Hash("ground_water"))
                {
                    m_position = {
                        GetRandomInt(size.width),
                        GetRandomInt(size.height)};
                }
            }

            void PlayerCharacter::MoveNorth()
            {
                m_position.y -= 1;
            }

            void PlayerCharacter::MoveEast()
            {
                m_position.x += 1;
            }

            void PlayerCharacter::MoveSouth()
            {
                m_position.y += 1;
            }

            void PlayerCharacter::MoveWest()
            {
                m_position.x -= 1;
            }
        }
    }
}