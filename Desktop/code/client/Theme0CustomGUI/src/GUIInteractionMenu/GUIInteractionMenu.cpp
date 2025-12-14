//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "GUIInteractionMenu.hpp"
#include "Actions.hpp"
#include "Mouse/MouseInput.hpp"
#include "Object.hpp"
#include "ObjectsStack.hpp"
#include "SDLDevice.hpp"
#include "TextRenderer.hpp"
#include "Tile.hpp"
#include "Update/TileHovering.hpp"
#include "World.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0
{
    void GUIInteractionMenu::Initialize()
    {
        this->SetVisible(false);

        for (auto i = 0; i < k_maxNumMenuEntries; i++)
        {
            m_renderIDsMenuEntryStrings.push_back(
                Hash("GUIInteractionMenuEntryString" + std::to_string(i)));
        }
    }

    void GUIInteractionMenu::BuildMenu()
    {
        m_entries.clear();

        auto hoveredCoordinate{_<GameplayCore::TileHovering>().GetHoveredCoordinate()};

        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto worldAreaSize{worldArea->GetSize()};

        m_clickedCoordinate = hoveredCoordinate;

        m_clickedRobot = worldArea->GetTile(hoveredCoordinate.x, hoveredCoordinate.y)->GetRobot();

        auto tile{worldArea->GetTile(hoveredCoordinate.x, hoveredCoordinate.y)};

        auto actionStop{GetAction<Hash("ActionStop")>()};

        m_entries.push_back({"Stop current action", actionStop.action});

        auto actionPickUp{GetAction<Hash("Pick up")>()};

        m_entries.push_back({"Pick up", actionPickUp.action});

        auto actionLayCobbleStone{GetAction<Hash("ActionLayCobbleStone")>()};

        m_entries.push_back({"Lay cobble stone", actionLayCobbleStone.action});

        auto actionLayMetalFloor{GetAction<Hash("ActionLayMetalFloor")>()};

        m_entries.push_back({"Lay metal floor", actionLayMetalFloor.action});

        auto actionClaimLand{GetAction<Hash("ActionClaimLand")>()};

        m_entries.push_back({"Claim land", actionClaimLand.action});

        auto actionPlowLand{GetAction<Hash("ActionPlowLand")>()};

        m_entries.push_back({"Plow land", actionPlowLand.action});

        auto actionChopTree{GetAction<Hash("ActionChopTree")>()};

        m_entries.push_back({"Chop tree", actionChopTree.action});

        auto actionSimpleShelter{GetAction<Hash("ActionBuildSimpleShelter")>()};

        m_entries.push_back({"Build simple shelter", actionSimpleShelter.action});

        auto actionForage{GetAction<Hash("ActionForage")>()};

        if (tile && !actionForage.groundMatches.empty() &&
            tile->GetGround() == actionForage.groundMatches[0])
        {
            m_entries.push_back({"Forage", actionForage.action});
        };

        auto objects{tile->GetObjectsStack()->GetObjects()};

        for (auto &object : objects)
        {
            auto type{object->GetType()};

            auto actionPickBranch{GetAction<Hash("ActionPickBranch")>()};

            for (const auto &actionObjectTypes : actionPickBranch.objectMatches)
            {
                if (type == actionObjectTypes)
                {
                    m_entries.push_back({"Pick branch", actionPickBranch.action});

                    break;
                }
            }

            auto actionPickStone{GetAction<Hash("ActionPickStone")>()};

            for (const auto &actionObjectTypes : actionPickStone.objectMatches)
            {
                if (type == actionObjectTypes)
                {
                    m_entries.push_back({"Pick stone", actionPickStone.action});

                    break;
                }
            }

            auto actionChipStone{GetAction<Hash("ActionChipStone")>()};

            for (const auto &actionObjectTypes : actionChipStone.objectMatches)
            {
                if (type == actionObjectTypes)
                {
                    m_entries.push_back({"Chip stone", actionChipStone.action});

                    break;
                }
            }

            auto actionSitByComputer{GetAction<Hash("ActionSitByComputer")>()};

            for (const auto &actionObjectTypes : actionSitByComputer.objectMatches)
            {
                if (type == actionObjectTypes)
                {

                    m_entries.push_back({"Sit by computer", actionSitByComputer.action});

                    break;
                }
            }
        }
    }

    void GUIInteractionMenu::UpdateDerived()
    {
        GUIPanel::UpdateDerived();

        auto newHeight{2 * 0.01f + k_lineHeight * (m_entries.size() + 1)};

        this->SetHeight(newHeight);

        auto bounds{this->GetBounds()};

        auto mousePosition{GetNormallizedMousePosition(_<SDLDevice>().GetWindow())};

        auto i{0};

        for (auto &entry : m_entries)
        {
            auto menuEntryRect{RectF{bounds.x + 0.01f + k_indentWidth,
                                     bounds.y + 0.01f + k_lineHeight * (i + 1), bounds.width,
                                     k_lineHeight}};

            if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenFired())
            {
                if (menuEntryRect.Contains(mousePosition))
                {
                    entry.GetAction()();
                }

                this->SetVisible(false);
            }

            ++i;
        }
        if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenFiredPickResult())
        {
            this->SetVisible(false);
        }
    }

    void GUIInteractionMenu::RenderDerived() const
    {
        GUIPanel::RenderDerived();

        auto bounds{this->GetBounds()};

        _<TextRenderer>().DrawString(k_renderIDActionsString, "Actions", bounds.x + 0.01f,
                                     bounds.y + 0.01f, FontSizes::_20, false, true,
                                     Palette::GetColor<Hash("YellowTransparent")>());

        auto i{0};

        for (auto &entry : m_entries)
        {
            _<TextRenderer>().DrawString(
                m_renderIDsMenuEntryStrings[i], entry.GetLabel(), bounds.x + 0.01f + k_indentWidth,
                bounds.y + 0.01f + (i + 1) * k_lineHeight, FontSizes::_20, false, true);

            ++i;
        }
    }
}