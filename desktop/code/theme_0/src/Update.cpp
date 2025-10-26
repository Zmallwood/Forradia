//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Update.hpp"

#include "Core.hpp"

#include "GUISpec.hpp"

#include "SDLDevice.hpp"

#include "Theme0Essentials.hpp"

#include "Theme0Properties.hpp"

#include "Utilities/NumbersUtilities.hpp"

#include "WorldStruct.hpp"

namespace Forradia
{
    namespace Theme0
    {
        namespace GameplayCore
        {
            void UpdateKeyboardActions()
            {
                if (_<Engine::Input::KeyboardInput>()
                        .KeyIsPressedPickResult(
                            SDLK_ESCAPE))
                {
                    _<GUISystemMenu>().ToggleVisibility();
                }
                else if (_<Engine::Input::KeyboardInput>()
                             .KeyIsPressedPickResult(
                                 SDLK_c))
                {
                    _<GUIPlayerBodyWindow>()
                        .ToggleVisibility();
                }
                else if (_<Engine::Input::KeyboardInput>()
                             .KeyIsPressedPickResult(
                                 SDLK_b))
                {
                    _<GUIInventoryWindow>()
                        .ToggleVisibility();
                }
            }

            void UpdateMouseActions()
            {
                if (_<Engine::Input::MouseInput::
                          RightMouseButton>()
                        .HasBeenFiredPickResult())
                {
                    _<GUIInteractionMenu>().BuildMenu();

                    _<GUIInteractionMenu>().SetVisible(
                        true);

                    _<GUIInteractionMenu>().SetPosition(
                        GetNormallizedMousePosition(
                            _<SDLDevice>().GetWindow()));
                }
            }

            void UpdateKeyboardMovement()
            {
                auto upPress{
                    _<Engine::Input::KeyboardInput>()
                        .KeyIsPressed(SDLK_UP)};

                auto rightPress{
                    _<Engine::Input::KeyboardInput>()
                        .KeyIsPressed(SDLK_RIGHT)};

                auto downPress{
                    _<Engine::Input::KeyboardInput>()
                        .KeyIsPressed(SDLK_DOWN)};

                auto leftPress{
                    _<Engine::Input::KeyboardInput>()
                        .KeyIsPressed(SDLK_LEFT)};

                auto wPress{
                    _<Engine::Input::KeyboardInput>()
                        .KeyIsPressed(SDLK_w)};

                auto aPress{
                    _<Engine::Input::KeyboardInput>()
                        .KeyIsPressed(SDLK_a)};

                auto sPress{
                    _<Engine::Input::KeyboardInput>()
                        .KeyIsPressed(SDLK_s)};

                auto dPress{
                    _<Engine::Input::KeyboardInput>()
                        .KeyIsPressed(SDLK_d)};

                if (upPress || rightPress || downPress ||
                    leftPress)
                {
                    _<Theme0::GameplayCore::
                          PlayerCharacter>()
                        .SetDestination({-1, -1});
                }

                auto now{GetTicks()};

                if (now >=
                        _<Theme0::GameplayCore::
                                PlayerCharacter>()
                                .GetTicksLastMovement() +
                            InvertMovementSpeed(
                                _<Theme0::GameplayCore::

                                      PlayerCharacter>()
                                    .GetMovementSpeed()) &&
                    (upPress || rightPress || downPress ||
                     leftPress || wPress || aPress ||
                     sPress || dPress))
                {
                    if (upPress || wPress)
                    {
                        _<Theme0::GameplayCore::
                              PlayerCharacter>()
                            .MoveNorth();
                    }

                    if (rightPress || dPress)
                    {
                        _<Theme0::GameplayCore::
                              PlayerCharacter>()
                            .MoveEast();
                    }

                    if (downPress || sPress)
                    {
                        _<Theme0::GameplayCore::
                              PlayerCharacter>()
                            .MoveSouth();
                    }

                    if (leftPress || aPress)
                    {
                        _<Theme0::GameplayCore::
                              PlayerCharacter>()
                            .MoveWest();
                    }

                    _<Theme0::GameplayCore::
                          PlayerCharacter>()
                        .SetTicksLastMovement(now);
                }
            }

            void UpdateMouseMovement()
            {
                if (_<Engine::Input::MouseInput::
                          LeftMouseButton>()
                        .HasBeenFiredPickResult())
                {
                    auto newDestination{
                        _<TileHovering>()
                            .GetHoveredCoordinate()};

                    _<Theme0::GameplayCore::
                          PlayerCharacter>()
                        .SetDestination(newDestination);
                }

                auto playerPosition{
                    _<PlayerCharacter>().GetPosition()};

                auto destination{
                    _<PlayerCharacter>().GetDestination()};

                if (destination == Point{-1, -1})
                {
                    return;
                }

                auto now{GetTicks()};

                if (now >= _<PlayerCharacter>()
                                   .GetTicksLastMovement() +
                               InvertMovementSpeed(
                                   _<PlayerCharacter>()
                                       .GetMovementSpeed()))
                {
                    auto dX{destination.x -
                            playerPosition.x};

                    auto dY{destination.y -
                            playerPosition.y};

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
                        _<PlayerCharacter>().SetDestination(
                            {-1, -1});
                    }

                    _<PlayerCharacter>()
                        .SetTicksLastMovement(now);
                }
            }

            void UpdateCreaturesMovement()
            {
                auto worldArea{
                    _<World>().GetCurrentWorldArea()};

                auto &creatures{
                    worldArea->GetCreaturesMirrorRef()};

                auto now{GetTicks()};

                for (auto it = creatures.begin();
                     it != creatures.end();)
                {
                    auto creature{it->first};

                    auto position{it->second};

                    if (now <
                        creature->GetTicksLastMovement() +
                            InvertMovementSpeed(
                                creature
                                    ->GetMovementSpeed()))
                    {
                        ++it;

                        continue;
                    }

                    auto destination{
                        creature->GetDestination()};

                    if (destination.x == -1 &&
                        destination.y == -1)
                    {
                        auto newDestination{
                            position.x + GetRandomInt(11) -
                            5};

                        auto newDestinationY{
                            position.y + GetRandomInt(11) -
                            5};

                        creature->SetDestination(
                            {newDestination,
                             newDestinationY});
                    }

                    auto worldArea{
                        _<World>().GetCurrentWorldArea()};

                    auto &creatures{
                        worldArea->GetCreaturesMirrorRef()};

                    auto dX{creature->GetDestination().x -
                            position.x};

                    auto dY{creature->GetDestination().y -
                            position.y};

                    auto normalizedDX{Normalize(dX)};

                    auto normalizedDY{Normalize(dY)};

                    auto newX{position.x + normalizedDX};

                    auto newY{position.y + normalizedDY};

                    Point newPosition{newX, newY};

                    if (newPosition ==
                        creature->GetDestination())
                    {
                        creature->SetDestination({-1, -1});
                    }

                    auto tile{worldArea->GetTile(
                        newPosition.x, newPosition.y)};

                    if (tile && !tile->GetCreature() &&
                        tile->GetGround() !=
                            Hash("ground_water"))
                    {
                        auto oldPosition{
                            creatures.at(creature)};

                        creature->SetTicksLastMovement(now);

                        auto oldTile{worldArea->GetTile(
                            oldPosition.x, oldPosition.y)};

                        auto newTile{worldArea->GetTile(
                            newPosition.x, newPosition.y)};

                        oldTile->SetCreature(nullptr);

                        newTile->SetCreature(creature);

                        creatures.erase(creature);

                        creatures.insert({creature,
                                          {newPosition.x,
                                           newPosition.y}});
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
                auto worldArea{
                    _<World>().GetCurrentWorldArea()};

                auto &npcs{worldArea->GetNPCsMirrorRef()};

                auto now{GetTicks()};

                for (auto it = npcs.begin();
                     it != npcs.end();)
                {
                    auto npc{it->first};

                    auto position{it->second};

                    if (now >
                        npc->GetTicksNextSpontaneousSpeech())
                    {
                        auto name{npc->GetName()};

                        if (GetRandomInt(20) == 0)
                        {
                            _<GUIChatBox>().Print(
                                name +
                                ": Buying blueberries, "
                                "one gold each.");
                        }
                        else
                        {
                            _<GUIChatBox>().Print(
                                name + ": Hello all!");
                        }

                        npc->SetTicksNextSpontaneousSpeech(
                            now + 5 * k_oneSecMillis +
                            (6000 * k_oneSecMillis));
                    }
                    if (now <
                        npc->GetTicksLastMovement() +
                            InvertMovementSpeed(
                                npc->GetMovementSpeed()))
                    {
                        ++it;

                        continue;
                    }

                    auto destination{npc->GetDestination()};

                    if (destination.x == -1 &&
                        destination.y == -1)
                    {
                        auto newDestinationX{
                            position.x + GetRandomInt(11) -
                            5};
                        auto newDestinationY{
                            position.y + GetRandomInt(11) -
                            5};

                        npc->SetDestination(
                            {newDestinationX,
                             newDestinationY});
                    }

                    auto dX{npc->GetDestination().x -
                            position.x};

                    auto dY{npc->GetDestination().y -
                            position.y};

                    auto normalizedDX{Normalize(dX)};

                    auto normalizedDY{Normalize(dY)};

                    auto newX{position.x + normalizedDX};

                    auto newY{position.y + normalizedDY};

                    auto newPosition{Point{newX, newY}};

                    if (newPosition ==
                        npc->GetDestination())
                    {
                        npc->SetDestination({-1, -1});
                    }

                    auto tile{worldArea->GetTile(
                        newPosition.x, newPosition.y)};

                    if (tile && !tile->GetNPC() &&
                        tile->GetGround() !=
                            Hash("ground_water"))
                    {
                        auto oldPosition{position};

                        npc->SetTicksLastMovement(now);

                        auto oldTile{worldArea->GetTile(
                            oldPosition.x, oldPosition.y)};

                        auto newTile{worldArea->GetTile(
                            newPosition.x, newPosition.y)};

                        oldTile->SetNPC(nullptr);

                        newTile->SetNPC(npc);

                        npcs.erase(npc);

                        npcs.insert({npc,
                                     {newPosition.x,
                                      newPosition.y}});
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

                auto worldArea{
                    _<World>().GetCurrentWorldArea()};

                auto worldAreaSize{worldArea->GetSize()};

                auto playerPos{
                    _<PlayerCharacter>().GetPosition()};

                auto rendTileSize{
                    _<Theme0Properties>().k_tileSize};

                auto mousePosition{
                    GetNormallizedMousePosition(
                        _<SDLDevice>().GetWindow())};

                auto canvasSize{GetCanvasSize(
                    _<SDLDevice>().GetWindow())};

                auto elevHeight{0.1f};

                auto playerElev{
                    worldArea
                        ->GetTile(worldAreaSize.width -
                                      playerPos.x,
                                  worldAreaSize.height -
                                      playerPos.y)
                        ->GetElevation()};

                Point3F cameraPos{
                    (worldAreaSize.width - playerPos.x) *
                            rendTileSize +
                        rendTileSize / 2,
                    (worldAreaSize.height - playerPos.y) *
                            rendTileSize +
                        rendTileSize / 2,
                    -playerElev * elevHeight};

                glm::mat4 modelMatrix = glm::mat4(1.0f);

                modelMatrix = glm::translate(
                    modelMatrix,
                    glm::vec3((worldAreaSize.width -
                               playerPos.x) *
                                  rendTileSize,
                              (worldAreaSize.height -
                               playerPos.y) *
                                  rendTileSize,
                              0.0f));

                glm::mat4 view = glm::lookAt(
                    glm::vec3(cameraPos.x,
                              cameraPos.y - 2.0f,
                              -cameraPos.z + 2.5f),
                    glm::vec3(cameraPos.x, cameraPos.y,
                              -cameraPos.z),
                    glm::vec3(0.0f, 0.0f, -1.0f));

                auto aspectRatio{CalcAspectRatio(
                    _<SDLDevice>().GetWindow())};

                glm::mat4 proj = glm::perspective(
                    90.0f, aspectRatio, 0.1f, 100.0f);

                auto c = glm::vec3(cameraPos.x,
                                   cameraPos.y - 2.0f,
                                   -cameraPos.z + 2.5f);

                auto gridSize{_<Theme0Properties>().k_gridSize};

                auto dir{glm::normalize(glm::unProject(
                    glm::vec3((mousePosition.x) *
                                  canvasSize.width,
                              (mousePosition.y) *
                                  canvasSize.height,
                              1),
                    view * modelMatrix, proj,
                    glm::vec4(0.0f, 0.0f, canvasSize.width,
                              canvasSize.height)))};

                auto extraRows{8};

                for (auto y = -extraRows;
                     y < gridSize.height + extraRows; y++)
                {
                    for (auto x = 0; x < gridSize.width;
                         x++)
                    {
                        auto xCoordinate{
                            (worldAreaSize.width -
                             playerPos.x) -
                            (gridSize.width - 1) / 2 + x};

                        auto yCoordinate{
                            (worldAreaSize.height -
                             playerPos.y) -
                            (gridSize.height - 1) / 2 + y};

                        if (!worldArea->IsValidCoordinate(
                                xCoordinate, yCoordinate))
                        {
                            continue;
                        }

                        auto coordinateNW{Point{
                            xCoordinate, yCoordinate}};

                        auto coordinateNE{Point{
                            xCoordinate + 1, yCoordinate}};

                        auto coordinateSW{Point{
                            xCoordinate, yCoordinate + 1}};

                        auto coordinateSE{
                            Point{xCoordinate + 1,
                                  yCoordinate + 1}};

                        auto tileNW{worldArea->GetTile(
                            coordinateNW)};

                        auto tileNE{worldArea->GetTile(
                            coordinateNE)};

                        auto tileSW{worldArea->GetTile(
                            coordinateSW)};

                        auto tileSE{worldArea->GetTile(
                            coordinateSE)};

                        auto elevationNW{
                            tileNW ? tileNW->GetElevation()
                                   : 0.0f};

                        auto elevationNE{
                            tileNE ? tileNE->GetElevation()
                                   : 0.0f};

                        auto elevationSE{
                            tileSE ? tileSE->GetElevation()
                                   : 0.0f};

                        auto elevationSW{
                            tileSW ? tileSW->GetElevation()
                                   : 0.0f};

                        auto v00{glm::vec3{
                            (xCoordinate - 1 + 0.5f) *
                                rendTileSize,
                            (yCoordinate - 1 + 0.5f) *
                                rendTileSize,
                            elevationNW * elevHeight}};

                        auto v10{glm::vec3{
                            (xCoordinate - 1 + 0.5f + 1) *
                                rendTileSize,
                            (yCoordinate - 1 + 0.5f) *
                                rendTileSize,
                            elevationNE * elevHeight}};

                        auto v11{glm::vec3{
                            (xCoordinate - 1 + 0.5f + 1) *
                                rendTileSize,
                            (yCoordinate - 1 + 0.5f + 1) *
                                rendTileSize,
                            elevationSE * elevHeight}};

                        auto v01{glm::vec3{
                            (xCoordinate - 1 + 0.5f) *
                                rendTileSize,
                            (yCoordinate - 1 + 0.5f + 1) *
                                rendTileSize,
                            elevationSW * elevHeight}};

                        glm::vec3 result;

                        auto success{
                            glm::intersectLineTriangle(
                                c, dir, v00, v10, v11,
                                result)};

                        if (!success)
                        {
                            success = {
                                glm::intersectLineTriangle(
                                    c, dir, v00, v11, v01,
                                    result)};
                        }

                        if (success)
                        {
                            m_hoveredCoordinate = {
                                (worldAreaSize.width -
                                 xCoordinate + 1),
                                (worldAreaSize.height -
                                 yCoordinate + 1)};
                        }
                    }
                }
            }
        }
    }
}