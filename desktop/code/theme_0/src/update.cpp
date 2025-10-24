/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "update.hpp"
#include "core.hpp"
#include "gui_spec.hpp"
#include "theme_0_core.hpp"
#include "world_struct.hpp"

_NS_START_
namespace Theme0
{
    namespace GameplayCore
    {
        void UpdateKeyboardActions()
        {
            if (_<Core::Engine::Input::KeyboardInput>().KeyIsPressedPickResult(
                    SDLK_ESCAPE))
            {
                _<GUISystemMenu>().ToggleVisibility();
            }
            else if (_<Core::Engine::Input::KeyboardInput>()
                         .KeyIsPressedPickResult(SDLK_c))
            {
                _<GUIPlayerBodyWindow>().ToggleVisibility();
            }
            else if (_<Core::Engine::Input::KeyboardInput>()
                         .KeyIsPressedPickResult(SDLK_b))
            {
                _<GUIInventoryWindow>().ToggleVisibility();
            }
        }

        void UpdateMouseActions()
        {
            if (_<Core::Engine::Input::MouseInput::RightMouseButton>()
                    .HasBeenFiredPickResult())
            {
                _<GUIInteractionMenu>().BuildMenu();

                _<GUIInteractionMenu>().SetVisible(true);

                _<GUIInteractionMenu>().SetPosition(GetNormallizedMousePosition(
                    _<Engine::SDLDevice>().GetWindow()));
            }
        }

        void UpdateKeyboardMovement()
        {
            auto upPress{
                _<Core::Engine::Input::KeyboardInput>().KeyIsPressed(SDLK_UP)};

            auto rightPress{
                _<Core::Engine::Input::KeyboardInput>().KeyIsPressed(
                    SDLK_RIGHT)};

            auto downPress{_<Core::Engine::Input::KeyboardInput>().KeyIsPressed(
                SDLK_DOWN)};

            auto leftPress{_<Core::Engine::Input::KeyboardInput>().KeyIsPressed(
                SDLK_LEFT)};

            auto wPress{
                _<Core::Engine::Input::KeyboardInput>().KeyIsPressed(SDLK_w)};
            auto aPress{
                _<Core::Engine::Input::KeyboardInput>().KeyIsPressed(SDLK_a)};
            auto sPress{
                _<Core::Engine::Input::KeyboardInput>().KeyIsPressed(SDLK_s)};
            auto dPress{
                _<Core::Engine::Input::KeyboardInput>().KeyIsPressed(SDLK_d)};

            if (upPress || rightPress || downPress || leftPress)
            {
                _<Theme0::GameplayCore::Player::PlayerCharacter>()
                    .SetDestination({-1, -1});
            }

            auto now{GetTicks()};

            if (now >=
                    _<Theme0::GameplayCore::Player::PlayerCharacter>()
                            .GetTicksLastMovement() +
                        InvertMovementSpeed(
                            _<Theme0::GameplayCore::Player::PlayerCharacter>()
                                .GetMovementSpeed()) &&
                (upPress || rightPress || downPress || leftPress || wPress ||
                 aPress || sPress || dPress))
            {
                if (upPress || wPress)
                {
                    _<Theme0::GameplayCore::Player::PlayerCharacter>()
                        .MoveNorth();
                }

                if (rightPress || dPress)
                {
                    _<Theme0::GameplayCore::Player::PlayerCharacter>()
                        .MoveEast();
                }

                if (downPress || sPress)
                {
                    _<Theme0::GameplayCore::Player::PlayerCharacter>()
                        .MoveSouth();
                }

                if (leftPress || aPress)
                {
                    _<Theme0::GameplayCore::Player::PlayerCharacter>()
                        .MoveWest();
                }

                _<Theme0::GameplayCore::Player::PlayerCharacter>()
                    .SetTicksLastMovement(now);
            }
        }

        void UpdateMouseMovement()
        {
            if (_<Core::Engine::Input::MouseInput::LeftMouseButton>()
                    .HasBeenFiredPickResult())
            {
                auto newDestination{_<TileHovering>().GetHoveredCoordinate()};

                _<Theme0::GameplayCore::Player::PlayerCharacter>()
                    .SetDestination(newDestination);
            }

            auto playerPosition{_<PlayerCharacter>().GetPosition()};

            auto destination{_<PlayerCharacter>().GetDestination()};

            if (destination == Point{-1, -1})
            {
                return;
            }

            auto now{GetTicks()};

            if (now >= _<PlayerCharacter>().GetTicksLastMovement() +
                           InvertMovementSpeed(
                               _<PlayerCharacter>().GetMovementSpeed()))
            {
                auto dX{destination.x - playerPosition.x};
                auto dY{destination.y - playerPosition.y};

                if (dX < 0)
                {
                    _<PlayerCharacter>().MoveWest();
                }

                if (dY < 0)
                {
                    _<PlayerCharacter>().MoveNorth();
                }

                if (dX > 0)
                {
                    _<PlayerCharacter>().MoveEast();
                }

                if (dY > 0)
                {
                    _<PlayerCharacter>().MoveSouth();
                }

                if (destination == playerPosition)
                {
                    _<PlayerCharacter>().SetDestination({-1, -1});
                }

                _<PlayerCharacter>().SetTicksLastMovement(now);
            }
        }

        void UpdateCreaturesMovement()
        {
            auto worldArea{_<World>().GetCurrentWorldArea()};

            auto &creatures{worldArea->GetCreaturesMirrorRef()};

            auto now{GetTicks()};

            for (auto it = creatures.begin(); it != creatures.end();)
            {
                auto creature{it->first};

                auto position{it->second};

                if (now < creature->GetTicksLastMovement() +
                              InvertMovementSpeed(creature->GetMovementSpeed()))
                {
                    ++it;

                    continue;
                }

                auto destination{creature->GetDestination()};

                if (destination.x == -1 && destination.y == -1)
                {
                    auto newDestination{position.x + GetRandomInt(11) - 5};

                    auto newDestinationY{position.y + GetRandomInt(11) - 5};

                    creature->SetDestination({newDestination, newDestinationY});
                }

                auto worldArea{_<World>().GetCurrentWorldArea()};

                auto &creatures{worldArea->GetCreaturesMirrorRef()};

                auto dX{creature->GetDestination().x - position.x};
                auto dY{creature->GetDestination().y - position.y};

                auto normalizedDX{Normalize(dX)};
                auto normalizedDY{Normalize(dY)};

                auto newX{position.x + normalizedDX};
                auto newY{position.y + normalizedDY};

                Point newPosition{newX, newY};

                if (newPosition == creature->GetDestination())
                {
                    creature->SetDestination({-1, -1});
                }

                auto tile{worldArea->GetTile(newPosition.x, newPosition.y)};

                if (tile && !tile->GetCreature() &&
                    tile->GetGround() != Hash("ground_water"))
                {
                    auto oldPosition{creatures.at(creature)};

                    creature->SetTicksLastMovement(now);

                    auto oldTile{
                        worldArea->GetTile(oldPosition.x, oldPosition.y)};

                    auto newTile{
                        worldArea->GetTile(newPosition.x, newPosition.y)};

                    oldTile->SetCreature(nullptr);

                    newTile->SetCreature(creature);

                    creatures.erase(creature);

                    creatures.insert(
                        {creature, {newPosition.x, newPosition.y}});
                }
                else
                {
                    creature->SetDestination({-1, -1});
                }

                ++it;
            }
        }

        void UpdateNPCs()
        {
            auto worldArea{_<World>().GetCurrentWorldArea()};

            auto &npcs{worldArea->GetNPCsMirrorRef()};

            auto now{GetTicks()};

            for (auto it = npcs.begin(); it != npcs.end();)
            {
                auto npc{it->first};

                auto position{it->second};

                if (now > npc->GetTicksNextSpontaneousSpeech())
                {
                    auto name{npc->GetName()};

                    if (GetRandomInt(20) == 0)
                    {
                        _<GUIComponentsLibrary::GUIChatBox>().Print(
                            name + ": Buying blueberries, one gold each.");
                    }
                    else
                    {
                        _<GUIComponentsLibrary::GUIChatBox>().Print(
                            name + ": Hello all!");
                    }

                    npc->SetTicksNextSpontaneousSpeech(
                        now + 5 * k_oneSecMillis + (6000 * k_oneSecMillis));
                }
                if (now < npc->GetTicksLastMovement() +
                              InvertMovementSpeed(npc->GetMovementSpeed()))
                {
                    ++it;

                    continue;
                }

                auto destination{npc->GetDestination()};

                if (destination.x == -1 && destination.y == -1)
                {
                    auto newDestinationX{position.x + GetRandomInt(11) - 5};
                    auto newDestinationY{position.y + GetRandomInt(11) - 5};

                    npc->SetDestination({newDestinationX, newDestinationY});
                }

                auto dX{npc->GetDestination().x - position.x};
                auto dY{npc->GetDestination().y - position.y};

                auto normalizedDX{Normalize(dX)};
                auto normalizedDY{Normalize(dY)};

                auto newX{position.x + normalizedDX};
                auto newY{position.y + normalizedDY};

                auto newPosition{Point{newX, newY}};

                if (newPosition == npc->GetDestination())
                {
                    npc->SetDestination({-1, -1});
                }

                auto tile{worldArea->GetTile(newPosition.x, newPosition.y)};

                if (tile && !tile->GetNPC() &&
                    tile->GetGround() != Hash("ground_water"))
                {
                    auto oldPosition{position};

                    npc->SetTicksLastMovement(now);

                    auto oldTile{
                        worldArea->GetTile(oldPosition.x, oldPosition.y)};

                    auto newTile{
                        worldArea->GetTile(newPosition.x, newPosition.y)};

                    oldTile->SetNPC(nullptr);

                    newTile->SetNPC(npc);

                    npcs.erase(npc);

                    npcs.insert({npc, {newPosition.x, newPosition.y}});
                }
                else
                {
                    npc->SetDestination({-1, -1});
                }

                ++it;
            }
        }

        void TileHovering::Update()
        {
            auto playerPosition{_<PlayerCharacter>().GetPosition()};

            auto mousePosition{GetNormallizedMousePosition(
                _<Engine::SDLDevice>().GetWindow())};

            auto tileSize{CalcTileSize()};

            auto screenRelativeX{CInt(mousePosition.x / tileSize.width)};

            auto gridSize{CalcGridSize()};

            auto hoveredXCoordinate{playerPosition.x -
                                    (gridSize.width - 1) / 2 + screenRelativeX};

            auto screenRelativeXPx{
                (hoveredXCoordinate -
                 (playerPosition.x - (gridSize.width - 1) / 2)) *
                tileSize.width};

            auto worldArea{_<World>().GetCurrentWorldArea()};

            auto extraRows{8};

            auto topYCoordinate{
                CInt(playerPosition.y - (gridSize.height - 1) / 2) - extraRows};

            auto playerTile{worldArea->GetTile(playerPosition)};

            auto playerElevation{
                playerTile ? worldArea->GetTile(playerPosition)->GetElevation()
                           : 0};

            auto screenRelativeYPx{-extraRows * tileSize.height};

            for (auto y = -extraRows; y < gridSize.height + extraRows; y++)
            {
                auto yCoordinate{
                    CInt(playerPosition.y - (gridSize.height - 1) / 2 + y)};

                auto coordinate{Point{hoveredXCoordinate, yCoordinate}};

                auto tile{worldArea->GetTile(coordinate)};

                if (!tile)
                {
                    screenRelativeYPx =
                        0.5f +
                        (y - (gridSize.height - 1) / 2) * tileSize.height +
                        playerElevation * tileSize.height / 2;

                    continue;
                }

                auto elevation{tile->GetElevation()};

                screenRelativeYPx =
                    0.5f + (y - (gridSize.height - 1) / 2) * tileSize.height +
                    (playerElevation - elevation) * tileSize.height / 2;

                auto coordinateNW{Point{coordinate.x, coordinate.y}};

                auto coordinateNE{Point{coordinate.x + 1, coordinate.y}};

                auto coordinateSW{Point{coordinate.x, coordinate.y + 1}};

                auto coordinateSE{Point{coordinate.x + 1, coordinate.y + 1}};

                if (!worldArea->IsValidCoordinate(coordinateNW.x,
                                                  coordinateNW.y) ||
                    !worldArea->IsValidCoordinate(coordinateNE.x,
                                                  coordinateNE.y) ||
                    !worldArea->IsValidCoordinate(coordinateSW.x,
                                                  coordinateSW.y) ||
                    !worldArea->IsValidCoordinate(coordinateSE.x,
                                                  coordinateSE.y))
                {
                    continue;
                }

                auto tileNW{worldArea->GetTile(coordinateNW)};
                auto tileNE{worldArea->GetTile(coordinateNE)};
                auto tileSW{worldArea->GetTile(coordinateSW)};
                auto tileSE{worldArea->GetTile(coordinateSE)};

                if (!tileNW || !tileNE || !tileSE || !tileSW)
                {
                    continue;
                }

                float localTileHeight;

                if (tileNW->GetElevation() > tileSW->GetElevation() &&
                    tileNE->GetElevation() > tileSE->GetElevation())
                {
                    localTileHeight = tileSize.height * 1.5f;
                }
                else if (tileNW->GetElevation() < tileSW->GetElevation() &&
                         tileNE->GetElevation() < tileSE->GetElevation())
                {
                    localTileHeight = tileSize.height * 0.5f;
                }
                else if (tileNE->GetElevation() > tileNW->GetElevation() &&
                         tileSE->GetElevation() > tileSW->GetElevation())
                {
                    localTileHeight = tileSize.height * 1.5f;
                }
                else if (tileNW->GetElevation() > tileNE->GetElevation() &&
                         tileSW->GetElevation() > tileSE->GetElevation())
                {
                    localTileHeight = tileSize.height * 1.5f;
                }
                else if (tileNW->GetElevation() > tileNE->GetElevation() &&
                         tileNW->GetElevation() > tileSE->GetElevation() &&
                         tileNW->GetElevation() > tileSW->GetElevation())
                {
                    localTileHeight = tileSize.height * 1.5f;
                }
                else if (tileNE->GetElevation() > tileNW->GetElevation() &&
                         tileNE->GetElevation() > tileSE->GetElevation() &&
                         tileNE->GetElevation() > tileSW->GetElevation())
                {
                    localTileHeight = tileSize.height * 1.5f;
                }
                else if (tileSW->GetElevation() > tileNW->GetElevation() &&
                         tileSW->GetElevation() > tileSE->GetElevation() &&
                         tileSW->GetElevation() > tileNE->GetElevation())
                {
                    localTileHeight = tileSize.height * 1.0f;
                }
                else if (tileSE->GetElevation() > tileNW->GetElevation() &&
                         tileSE->GetElevation() > tileNE->GetElevation() &&
                         tileSE->GetElevation() > tileSW->GetElevation())
                {
                    localTileHeight = tileSize.height * 1.0f;
                }
                else if (tileSW->GetElevation() < tileNW->GetElevation() &&
                         tileSW->GetElevation() < tileNE->GetElevation() &&
                         tileSW->GetElevation() < tileSE->GetElevation())
                {
                    localTileHeight = tileSize.height * 1.5f;
                }
                else if (tileSE->GetElevation() < tileNW->GetElevation() &&
                         tileSE->GetElevation() < tileNE->GetElevation() &&
                         tileSE->GetElevation() < tileSW->GetElevation())
                {
                    localTileHeight = tileSize.height * 1.5f;
                }
                else if (tileNW->GetElevation() < tileNE->GetElevation() &&
                         tileNW->GetElevation() < tileSW->GetElevation() &&
                         tileNW->GetElevation() < tileSE->GetElevation())
                {
                    localTileHeight = tileSize.height * 1.0f;
                }
                else if (tileNE->GetElevation() < tileNW->GetElevation() &&
                         tileNE->GetElevation() < tileSW->GetElevation() &&
                         tileNE->GetElevation() < tileSE->GetElevation())
                {
                    localTileHeight = tileSize.height * 1.0f;
                }
                else if (tileSW->GetElevation() == tileNE->GetElevation() &&
                         tileNW->GetElevation() < tileSW->GetElevation() &&
                         tileSE->GetElevation() < tileSW->GetElevation())
                {
                    localTileHeight = tileSize.height * 1.5f;
                }
                else if (tileNW->GetElevation() == tileSE->GetElevation() &&
                         tileNE->GetElevation() < tileNW->GetElevation() &&
                         tileSW->GetElevation() < tileNW->GetElevation())
                {
                    localTileHeight = tileSize.height * 1.5f;
                }
                else
                {
                    localTileHeight = tileSize.height;
                }

                auto rectangle{RectF{screenRelativeXPx,
                                     screenRelativeYPx - localTileHeight / 2,
                                     tileSize.width, localTileHeight}};

                if (rectangle.Contains(mousePosition))
                {
                    m_hoveredCoordinate = {hoveredXCoordinate, yCoordinate};

                    return;
                }
            }
        }
    }
}
_NS_END_