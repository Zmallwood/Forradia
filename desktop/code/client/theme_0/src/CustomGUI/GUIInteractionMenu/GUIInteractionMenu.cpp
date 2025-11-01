//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIInteractionMenu.hpp"

#include "World.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "ObjectsStack.hpp"

#include "Object.hpp"

#include "GUIChatBox.hpp"

#include "SDLDevice.hpp"

#include "Mouse/MouseInput.hpp"

#include "Text/TextRenderer.hpp"

#include "Update/TileHovering.hpp"

#include "PlayerCharacter.hpp"

#include "ObjectsInventory.hpp"

#include "Actions.hpp"

namespace Forradia::Theme0
{
    void GUIInteractionMenu::Initialize()
    {
        this->SetVisible(false);
    }

    void GUIInteractionMenu::BuildMenu()
    {
        m_entries.clear();

        auto hoveredCoordinate{
            _<GameplayCore::TileHovering>()
                .GetHoveredCoordinate()};

        m_clickedCoordinate = hoveredCoordinate;

        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto worldAreaSize{worldArea->GetSize()};

        auto tile{worldArea->GetTile(
            worldAreaSize.width - hoveredCoordinate.x,
            worldAreaSize.height - hoveredCoordinate.y)};

        auto actionStop{GetAction<Hash("ActionStop")>()};

        m_entries.push_back(
            {"Stop current action", actionStop.action});

        auto actionChopDownTrees{
            GetAction<Hash("ActionChopTrees")>()};

        m_entries.push_back({"Chop down trees",
                             actionChopDownTrees.action});

        auto actionSimpleShelter{
            GetAction<Hash("ActionBuildSimpleShelter")>()};

        m_entries.push_back({"Build simple shelter",
                             actionSimpleShelter.action});

        auto actionForage{
            GetAction<Hash("ActionForage")>()};

        if (tile && !actionForage.groundMatches.empty() &&
            tile->GetGround() ==
                actionForage.groundMatches[0])
        {
            m_entries.push_back(
                {"Forage", actionForage.action});
        };

        auto objects{tile->GetObjectsStack()->GetObjects()};

        for (auto &object : objects)
        {
            auto type{object->GetType()};

            auto action{
                GetAction<Hash("ActionPickBranch")>()};

            for (const auto &actionObjectTypes :
                 action.objectMatches)
            {
                if (type == actionObjectTypes)
                {
                    m_entries.push_back(
                        {"Pick branch", action.action});

                    break;
                }
            }
        }
    }

    void GUIInteractionMenu::UpdateDerived()
    {
        GUIPanel::UpdateDerived();

        auto bounds{this->GetBounds()};

        auto mousePosition{GetNormallizedMousePosition(
            _<SDLDevice>().GetWindow())};

        auto i{0};

        for (auto &entry : m_entries)
        {
            auto menuEntryRect{RectF{
                bounds.x + 0.01f + k_indentWidth,
                bounds.y + 0.01f + k_lineHeight * (i + 1),
                bounds.width, k_lineHeight}};

            if (_<MouseInput>()
                    .GetLeftMouseButtonRef()
                    .HasBeenFired())
            {
                if (menuEntryRect.Contains(mousePosition))
                {
                    entry.GetAction()();
                }

                this->SetVisible(false);
            }

            ++i;
        }
        if (_<MouseInput>()
                .GetLeftMouseButtonRef()
                .HasBeenFiredPickResult())
        {
            this->SetVisible(false);
        }
    }

    void GUIInteractionMenu::RenderDerived() const
    {
        GUIPanel::RenderDerived();

        auto bounds{this->GetBounds()};

        _<TextRenderer>().DrawString(
            "Actions", bounds.x + 0.01f, bounds.y + 0.01f,
            FontSizes::_20, false,
            Palette::GetColor<Hash("YellowTransparent")>());

        auto i{0};

        for (auto &entry : m_entries)
        {
            _<TextRenderer>().DrawString(
                entry.GetLabel(),
                bounds.x + 0.01f + k_indentWidth,
                bounds.y + 0.01f + (i + 1) * k_lineHeight,

                FontSizes::_20);

            ++i;
        }
    }
}