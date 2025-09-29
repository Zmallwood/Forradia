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

        auto overallBodyStrength{playerBody.GetStrength()};
        auto rightArmStrength{playerBody.GetRightArmRef().GetStrength()};
        auto leftArmStrength{playerBody.GetLeftArmRef().GetStrength()};
        auto legsStrength{playerBody.GetLegsRef().GetStrength()};
        auto overallBodyMaxEnergy{playerBody.GetMaxEnergy()};
        auto rightArmMaxEnergy{playerBody.GetRightArmRef().GetMaxEnergy()};
        auto leftArmMaxEnergy{playerBody.GetLeftArmRef().GetMaxEnergy()};
        auto legsMaxEnergy{playerBody.GetLegsRef().GetMaxEnergy()};
        auto overallBodyTemperature{playerBody.GetTemperature()};
        auto rightArmTemperature{playerBody.GetRightArmRef().GetTemperature()};
        auto leftArmTemperature{playerBody.GetLeftArmRef().GetTemperature()};
        auto legsTemperature{playerBody.GetLegsRef().GetTemperature()};

        auto ssOverallBodyStrength {fmt::format("Overall body strength: {:.2f}", overallBodyStrength)};
        auto ssRightArmStrength {fmt::format("Right arm strength: {:.2f}", rightArmStrength)};
        auto ssLeftArmStrength {fmt::format("Left arm strength: {:.2f}", leftArmStrength)};
        auto ssLegsStrength {fmt::format("Legs strength: {:.2f}", legsStrength)};
        auto ssOverallBodyMaxEnergy {fmt::format("Overall body max energy: {:.2f}", overallBodyMaxEnergy)};
        auto ssRightArmMaxEnergy {fmt::format("Right arm max energy: {:.2f}", rightArmMaxEnergy)};
        auto ssLeftArmMaxEnergy {fmt::format("Left arm max energy: {:.2f}", leftArmMaxEnergy)};
        auto ssLegsMaxEnergy {fmt::format("Legs max energy: {:.2f}", legsMaxEnergy)};
        auto ssOverallBodyTemperature {fmt::format("Overall body temperature: {:.2f}", overallBodyTemperature)};
        auto ssRightArmTemperature {fmt::format("Right arm temperature: {:.2f}", rightArmTemperature)};
        auto ssLeftArmTemperature {fmt::format("Left arm temperature: {:.2f}", leftArmTemperature)};
        auto ssLegsTemperature {fmt::format("Legs temperature: {:.2f}", legsTemperature)};

        auto bounds{GetBounds()};

        _<TextRenderer>().DrawString(ssOverallBodyStrength.data(), bounds.x + 0.01f, bounds.y + 0.04f + 1 * 0.03f);
        _<TextRenderer>().DrawString(ssRightArmStrength, bounds.x + 0.01f, bounds.y + 0.04f + 2 * 0.03f);
        _<TextRenderer>().DrawString(ssLeftArmStrength, bounds.x + 0.01f, bounds.y + 0.04f + 3 * 0.03f);
        _<TextRenderer>().DrawString(ssLegsStrength, bounds.x + 0.01f, bounds.y + 0.04f + 4 * 0.03f);
        _<TextRenderer>().DrawString(ssOverallBodyMaxEnergy, bounds.x + 0.01f, bounds.y + 0.04f + 5 * 0.03f);
        _<TextRenderer>().DrawString(ssRightArmMaxEnergy, bounds.x + 0.01f, bounds.y + 0.04f + 6 * 0.03f);
        _<TextRenderer>().DrawString(ssLeftArmMaxEnergy, bounds.x + 0.01f, bounds.y + 0.04f + 7 * 0.03f);
        _<TextRenderer>().DrawString(ssLegsMaxEnergy, bounds.x + 0.01f, bounds.y + 0.04f + 8 * 0.03f);
        _<TextRenderer>().DrawString(ssOverallBodyTemperature, bounds.x + 0.01f, bounds.y + 0.04f + 9 * 0.03f);
        _<TextRenderer>().DrawString(ssRightArmTemperature, bounds.x + 0.01f, bounds.y + 0.04f + 10 * 0.03f);
        _<TextRenderer>().DrawString(ssLeftArmTemperature, bounds.x + 0.01f, bounds.y + 0.04f + 11 * 0.03f);
        _<TextRenderer>().DrawString(ssLegsTemperature, bounds.x + 0.01f, bounds.y + 0.04f + 12 * 0.03f);
    }
}