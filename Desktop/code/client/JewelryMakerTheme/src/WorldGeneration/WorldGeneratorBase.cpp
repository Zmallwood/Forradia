/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGeneratorBase.hpp"
#include <cmath>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Properties/ThemeProperties.hpp"
#include "WorldStructure/World.hpp"
#include "WorldStructure/WorldArea.hpp"
#include "Player/Player.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldGeneratorBase::prepare() -> void
    {
        WorldGeneratorBase::loadParameters();

        m_worldArea = JewelryMakerTheme::World::instance().getWorldArea(
            Player::instance().getWorldAreaCoordinate());
        m_worldAreaSize = m_worldArea->getSize();
        m_worldScaling = JewelryMakerTheme::ThemeProperties::getWorldScaling();

        m_worldAreaLowerFloors = JewelryMakerTheme::World::instance().getWorldArea(
            Player::instance().getWorldAreaCoordinate().offset(Point3{0, 0, -1}));
        m_worldAreaLowerFloorsSize = m_worldAreaLowerFloors->getSize();
        m_worldScalingLowerFloors = JewelryMakerTheme::ThemeProperties::getWorldScaling();
    }

    auto WorldGeneratorBase::loadParameters() -> void
    {
        std::ifstream file("Resources/Data/WorldGenerationParameters.json");

        if (!file.is_open())
        {
            return;
        }

        nlohmann::json jsonData;

        try
        {
            file >> jsonData;
            file.close();
        }
        catch (const std::exception &)
        {
            return;
        }

        for (auto &[key, val] : jsonData.items())
        {
            if (val.is_number_integer())
            {
                m_parameters[hash(key)] = val.get<int>();
            }
            else if (val.is_number_float())
            {
                m_parameters[hash(key)] = val.get<float>();
            }
            else
            {
                printLine("Unsupported type for key: " + key);
            }
        }
    }
}
