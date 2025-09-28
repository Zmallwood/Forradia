/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUIPlayerStatsWindow.hpp"
#include "Core/Rendering/Text/TextRenderer.hpp"
#include "Theme0/Theme0Mechanics/CoreGameObjects/Player.hpp"

namespace Forradia
{
    void GUIPlayerStatsWindow::RenderDerived() const
    {
        GUIWindow::RenderDerived();

        auto &playerStats{_<Player>().GetPlayerStatsRef()};

        auto overallBodyStrength {playerStats.GetOverallBodyStrength()};
        auto rightArmStrength {playerStats.GetRightArmStrength()};
        auto leftArmStrength {playerStats.GetLeftArmStrength()};
        auto legsStrength {playerStats.GetLegsStrength()};
        auto overallBodyMaxEnergy {playerStats.GetOverallBodyMaxEnergy()};
        auto rightArmMaxEnergy {playerStats.GetRightArmMaxEnergy()};
        auto leftArmMaxEnergy {playerStats.GetLeftArmMaxEnergy()};
        auto legsMaxEnergy {playerStats.GetLegsMaxEnergy()};

        StringStream ssOverallBodyStrength;
        StringStream ssRightArmStrength;
        StringStream ssLeftArmStrength;
        StringStream ssLegsStrength;
        StringStream ssOverallBodyMaxEnergy;
        StringStream ssRightArmMaxEnergy;
        StringStream ssLeftArmMaxEnergy;
        StringStream ssLegsMaxEnergy;

        ssOverallBodyStrength << overallBodyStrength;
        ssRightArmStrength << rightArmStrength;
        ssLeftArmStrength << leftArmStrength;
        ssLegsStrength << legsStrength;
        ssOverallBodyMaxEnergy << overallBodyMaxEnergy;
        ssRightArmMaxEnergy << rightArmMaxEnergy;
        ssLeftArmMaxEnergy << leftArmMaxEnergy;
        ssLegsMaxEnergy << legsMaxEnergy;

        ssOverallBodyStrength.precision(2);
        ssRightArmStrength.precision(2);
        ssLeftArmStrength.precision(2);
        ssLegsStrength.precision(2);
        ssOverallBodyMaxEnergy.precision(2);
        ssRightArmMaxEnergy.precision(2);
        ssLeftArmMaxEnergy.precision(2);
        ssLegsMaxEnergy.precision(2);

        auto bounds{GetBounds()};

        _<TextRenderer>().DrawString("Overall body strength: " + ssOverallBodyStrength.str(), bounds.x + 0.01f, bounds.y + 0.04f + 1*0.03f);
        _<TextRenderer>().DrawString("Right arm strength: " + ssRightArmStrength.str(), bounds.x + 0.01f, bounds.y + 0.04f + 2*0.03f);
        _<TextRenderer>().DrawString("Left arm strength: " + ssLeftArmStrength.str(), bounds.x + 0.01f, bounds.y + 0.04f + 3*0.03f);
        _<TextRenderer>().DrawString("Legs strength: " + ssLegsStrength.str(), bounds.x + 0.01f, bounds.y + 0.04f + 4*0.03f);
        _<TextRenderer>().DrawString("Overall body energy: " + ssOverallBodyMaxEnergy.str(), bounds.x + 0.01f, bounds.y + 0.04f + 5*0.03f);
        _<TextRenderer>().DrawString("Overall right arm max energy: " + ssRightArmMaxEnergy.str(), bounds.x + 0.01f, bounds.y + 0.04f + 6*0.03f);
        _<TextRenderer>().DrawString("Overall left arm max energy: " + ssLeftArmMaxEnergy.str(), bounds.x + 0.01f, bounds.y + 0.04f + 7*0.03f);
        _<TextRenderer>().DrawString("Overall legs max energy: " + ssLegsMaxEnergy.str(), bounds.x + 0.01f, bounds.y + 0.04f + 8*0.03f);
    }
}