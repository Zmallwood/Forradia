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

#include "GUICore/GUIChatBox.hpp"

#include "SDLDevice.hpp"

#include "Input/Mouse/MouseInput.hpp"

#include "Rendering/Text/TextRenderer.hpp"

#include "Update/TileHovering.hpp"

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

        if (tile &&
            tile->GetGround() == Hash("GroundGrass"))
        {
            m_entries.push_back(
                {"Forage", [=]()
                 {
                     _<GUIChatBox>().Print(
                         "Grass foraged. You "
                         "found blue berries.");
                 }});
        }

        auto objects{tile->GetObjectsStack()->GetObjects()};

        for (auto &object : objects)
        {
            auto type{object->GetType()};

            if (type == Hash("ObjectFirTree"))
            {
                m_entries.push_back(
                    {"Cut down tree", [=]()
                     {
                         tile->GetObjectsStack()
                             ->RemoveObjectOfType(
                                 "ObjectFirTree");
                         tile->GetObjectsStack()->AddObject(
                             "ObjectFelledTree");
                         _<GUIChatBox>().Print(
                             "Tree cut down. "
                             "You found some "
                             "wood.");
                     }});
            }

            if (type == Hash("ObjectBirchTree"))
            {
                m_entries.push_back(
                    {"Cut down tree", [=]()
                     {
                         tile->GetObjectsStack()
                             ->RemoveObjectOfType(
                                 "ObjectBirchTree");
                         tile->GetObjectsStack()->AddObject(
                             "ObjectFelledTree");
                         _<GUIChatBox>().Print(
                             "Tree cut down. "
                             "You found some "
                             "wood.");
                     }});
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
            Colors::YellowTransparent);

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