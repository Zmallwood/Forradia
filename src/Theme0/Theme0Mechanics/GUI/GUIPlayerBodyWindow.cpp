/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUIPlayerBodyWindow.hpp"
#include "Core/Rendering/Text/TextRenderer.hpp"
#include "Theme0/Theme0Mechanics/CoreGameObjects/Player.hpp"

namespace Forradia
{
    void GUIPlayerBodyWindow::RenderDerived() const
    {
        GUIWindow::RenderDerived();

        auto &playerBody{_<Player>().GetPlayerBodyRef()};

        auto overallBodyStrength{playerBody.GetOverallBodyRef().GetStrength()};
        auto rightArmStrength{playerBody.GetRightArmRef().GetStrength()};
        auto leftArmStrength{playerBody.GetLeftArmRef().GetStrength()};
        auto legsStrength{playerBody.GetLegsRef().GetStrength()};
        auto overallBodyMaxEnergy{playerBody.GetOverallBodyRef().GetMaxEnergy()};
        auto rightArmMaxEnergy{playerBody.GetRightArmRef().GetMaxEnergy()};
        auto leftArmMaxEnergy{playerBody.GetLeftArmRef().GetMaxEnergy()};
        auto legsMaxEnergy{playerBody.GetLegsRef().GetMaxEnergy()};
        auto overallBodyTemperature{playerBody.GetOverallBodyRef().GetTemperature()};
        auto rightArmTemperature{playerBody.GetRightArmRef().GetTemperature()};
        auto leftArmTemperature{playerBody.GetLeftArmRef().GetTemperature()};
        auto legsTemperature{playerBody.GetLegsRef().GetTemperature()};

        StringStream ssOverallBodyStrength;
        StringStream ssRightArmStrength;
        StringStream ssLeftArmStrength;
        StringStream ssLegsStrength;
        StringStream ssOverallBodyMaxEnergy;
        StringStream ssRightArmMaxEnergy;
        StringStream ssLeftArmMaxEnergy;
        StringStream ssLegsMaxEnergy;
        StringStream ssOverallBodyTemperature;
        StringStream ssRightArmTemperature;
        StringStream ssLeftArmTemperature;
        StringStream ssLegsTemperature;

        ssOverallBodyStrength << overallBodyStrength;
        ssRightArmStrength << rightArmStrength;
        ssLeftArmStrength << leftArmStrength;
        ssLegsStrength << legsStrength;
        ssOverallBodyMaxEnergy << overallBodyMaxEnergy;
        ssRightArmMaxEnergy << rightArmMaxEnergy;
        ssLeftArmMaxEnergy << leftArmMaxEnergy;
        ssLegsMaxEnergy << legsMaxEnergy;
        ssOverallBodyTemperature << overallBodyTemperature;
        ssRightArmTemperature << rightArmTemperature;
        ssLeftArmTemperature << leftArmTemperature;
        ssLegsTemperature << legsTemperature;

        ssOverallBodyStrength.precision(2);
        ssRightArmStrength.precision(2);
        ssLeftArmStrength.precision(2);
        ssLegsStrength.precision(2);
        ssOverallBodyMaxEnergy.precision(2);
        ssRightArmMaxEnergy.precision(2);
        ssLeftArmMaxEnergy.precision(2);
        ssLegsMaxEnergy.precision(2);
        ssOverallBodyTemperature.precision(2);
        ssRightArmTemperature.precision(2);
        ssLeftArmTemperature.precision(2);
        ssLegsTemperature.precision(2);

        auto bounds{GetBounds()};

        _<TextRenderer>().DrawString("Overall body strength: " + ssOverallBodyStrength.str(), bounds.x + 0.01f, bounds.y + 0.04f + 1 * 0.03f);
        _<TextRenderer>().DrawString("Right arm strength: " + ssRightArmStrength.str(), bounds.x + 0.01f, bounds.y + 0.04f + 2 * 0.03f);
        _<TextRenderer>().DrawString("Left arm strength: " + ssLeftArmStrength.str(), bounds.x + 0.01f, bounds.y + 0.04f + 3 * 0.03f);
        _<TextRenderer>().DrawString("Legs strength: " + ssLegsStrength.str(), bounds.x + 0.01f, bounds.y + 0.04f + 4 * 0.03f);
        _<TextRenderer>().DrawString("Overall body max energy: " + ssOverallBodyMaxEnergy.str(), bounds.x + 0.01f, bounds.y + 0.04f + 5 * 0.03f);
        _<TextRenderer>().DrawString("Overall right arm max energy: " + ssRightArmMaxEnergy.str(), bounds.x + 0.01f, bounds.y + 0.04f + 6 * 0.03f);
        _<TextRenderer>().DrawString("Overall left arm max energy: " + ssLeftArmMaxEnergy.str(), bounds.x + 0.01f, bounds.y + 0.04f + 7 * 0.03f);
        _<TextRenderer>().DrawString("Overall legs max energy: " + ssLegsMaxEnergy.str(), bounds.x + 0.01f, bounds.y + 0.04f + 8 * 0.03f);
        _<TextRenderer>().DrawString("Overall body temperature: " + ssLegsTemperature.str(), bounds.x + 0.01f, bounds.y + 0.04f + 9 * 0.03f);
        _<TextRenderer>().DrawString("Right arm temperature: " + ssLegsTemperature.str(), bounds.x + 0.01f, bounds.y + 0.04f + 10 * 0.03f);
        _<TextRenderer>().DrawString("Left arm temperature: " + ssLegsTemperature.str(), bounds.x + 0.01f, bounds.y + 0.04f + 11 * 0.03f);
        _<TextRenderer>().DrawString("Legs temperature: " + ssLegsTemperature.str(), bounds.x + 0.01f, bounds.y + 0.04f + 12 * 0.03f);
    }
}