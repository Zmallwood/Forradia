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
            else if (_<Core::Engine::Input::KeyboardInput>().KeyIsPressedPickResult(
                         SDLK_c))
            {
                _<GUIPlayerBodyWindow>().ToggleVisibility();
            }
            else if (_<Core::Engine::Input::KeyboardInput>().KeyIsPressedPickResult(
                         SDLK_b))
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

                _<GUIInteractionMenu>().SetPosition(
                    GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow()));
            }
        }

        void UpdateKeyboardMovement()
        {
            auto up_press{
                _<Core::Engine::Input::KeyboardInput>().KeyIsPressed(SDLK_UP)};

            auto right_press{
                _<Core::Engine::Input::KeyboardInput>().KeyIsPressed(SDLK_RIGHT)};

            auto down_press{
                _<Core::Engine::Input::KeyboardInput>().KeyIsPressed(SDLK_DOWN)};

            auto left_press{
                _<Core::Engine::Input::KeyboardInput>().KeyIsPressed(SDLK_LEFT)};

            auto w_press{_<Core::Engine::Input::KeyboardInput>().KeyIsPressed(SDLK_w)};
            auto a_press{_<Core::Engine::Input::KeyboardInput>().KeyIsPressed(SDLK_a)};
            auto s_press{_<Core::Engine::Input::KeyboardInput>().KeyIsPressed(SDLK_s)};
            auto d_press{_<Core::Engine::Input::KeyboardInput>().KeyIsPressed(SDLK_d)};

            if (up_press || right_press || down_press || left_press)
            {
                _<Theme0::GameplayCore::Player::PlayerCharacter>().SetDestination({-1, -1});
            }

            auto now{GetTicks()};

            if (now >=
                    _<Theme0::GameplayCore::Player::PlayerCharacter>()
                            .GetTicksLastMovement() +
                        InvertMovementSpeed(_<Theme0::GameplayCore::Player::PlayerCharacter>()
                                          .GetMovementSpeed()) &&
                (up_press || right_press || down_press || left_press ||
                 w_press || a_press || s_press || d_press))
            {
                if (up_press || w_press)
                {
                    _<Theme0::GameplayCore::Player::PlayerCharacter>().MoveNorth();
                }

                if (right_press || d_press)
                {
                    _<Theme0::GameplayCore::Player::PlayerCharacter>().MoveEast();
                }

                if (down_press || s_press)
                {
                    _<Theme0::GameplayCore::Player::PlayerCharacter>().MoveSouth();
                }

                if (left_press || a_press)
                {
                    _<Theme0::GameplayCore::Player::PlayerCharacter>().MoveWest();
                }

                _<Theme0::GameplayCore::Player::PlayerCharacter>().SetTicksLastMovement(
                    now);
            }
        }

        void UpdateMouseMovement()
        {
            if (_<Core::Engine::Input::MouseInput::LeftMouseButton>()
                    .HasBeenFiredPickResult())
            {
                auto new_dest{_<TileHovering>().GetHoveredCoordinate()};

                _<Theme0::GameplayCore::Player::PlayerCharacter>().SetDestination(new_dest);
            }

            auto player_pos{_<PlayerCharacter>().GetPosition()};

            auto dest{_<PlayerCharacter>().GetDestination()};

            if (dest == Point{-1, -1})
            {
                return;
            }

            auto now{GetTicks()};

            if (now >= _<PlayerCharacter>().GetTicksLastMovement() +
                           InvertMovementSpeed(_<PlayerCharacter>().GetMovementSpeed()))
            {
                auto dx{dest.x - player_pos.x};
                auto dy{dest.y - player_pos.y};

                if (dx < 0)
                {
                    _<PlayerCharacter>().MoveWest();
                }

                if (dy < 0)
                {
                    _<PlayerCharacter>().MoveNorth();
                }

                if (dx > 0)
                {
                    _<PlayerCharacter>().MoveEast();
                }

                if (dy > 0)
                {
                    _<PlayerCharacter>().MoveSouth();
                }

                if (dest == player_pos)
                {
                    _<PlayerCharacter>().SetDestination({-1, -1});
                }

                _<PlayerCharacter>().SetTicksLastMovement(now);
            }
        }

        void UpdateCreaturesMovement()
        {
            auto w_area{_<World>().GetCurrentWorldArea()};

            auto &creas{w_area->GetCreaturesMirrorRef()};

            auto now{GetTicks()};

            for (auto it = creas.begin(); it != creas.end();)
            {
                auto crea{it->first};

                auto pos{it->second};

                if (now <
                    crea->GetTicksLastMovement() + InvertMovementSpeed(crea->GetMovementSpeed()))
                {
                    ++it;

                    continue;
                }

                auto dest{crea->GetDestination()};

                if (dest.x == -1 && dest.y == -1)
                {
                    auto new_dest{pos.x + GetRandomInt(11) - 5};

                    auto new_destination_y{pos.y + GetRandomInt(11) - 5};

                    crea->SetDestination({new_dest, new_destination_y});
                }

                auto w_area{_<World>().GetCurrentWorldArea()};

                auto &creas{w_area->GetCreaturesMirrorRef()};

                auto dx{crea->GetDestination().x - pos.x};
                auto dy{crea->GetDestination().y - pos.y};

                auto norm_dx{Normalize(dx)};
                auto norm_dy{Normalize(dy)};

                auto new_x{pos.x + norm_dx};
                auto new_y{pos.y + norm_dy};

                Point new_pos{new_x, new_y};

                if (new_pos == crea->GetDestination())
                {
                    crea->SetDestination({-1, -1});
                }

                auto tl{w_area->GetTile(new_pos.x, new_pos.y)};

                if (tl && !tl->GetCreature() &&
                    tl->GetGround() != Hash("ground_water"))
                {
                    auto old_pos{creas.at(crea)};

                    crea->SetTicksLastMovement(now);

                    auto old_tile{w_area->GetTile(old_pos.x, old_pos.y)};

                    auto new_tile{w_area->GetTile(new_pos.x, new_pos.y)};

                    old_tile->SetCreature(nullptr);

                    new_tile->SetCreature(crea);

                    creas.erase(crea);

                    creas.insert({crea, {new_pos.x, new_pos.y}});
                }
                else
                {
                    crea->SetDestination({-1, -1});
                }

                ++it;
            }
        }

        void UpdateNPCs()
        {
            auto w_area{_<World>().GetCurrentWorldArea()};

            auto &npcs{w_area->GetNPCsMirrorRef()};

            auto now{GetTicks()};

            for (auto it = npcs.begin(); it != npcs.end();)
            {
                auto npc{it->first};

                auto pos{it->second};

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
                        now + 5 * k_one_sec_millis + (6000 * k_one_sec_millis));
                }
                if (now <
                    npc->GetTicksLastMovement() + InvertMovementSpeed(npc->GetMovementSpeed()))
                {
                    ++it;

                    continue;
                }

                auto dest{npc->GetDestination()};

                if (dest.x == -1 && dest.y == -1)
                {
                    auto new_dest_x{pos.x + GetRandomInt(11) - 5};
                    auto new_dest_y{pos.y + GetRandomInt(11) - 5};

                    npc->SetDestination({new_dest_x, new_dest_y});
                }

                auto dx{npc->GetDestination().x - pos.x};
                auto dy{npc->GetDestination().y - pos.y};

                auto norm_dx{Normalize(dx)};
                auto norm_dy{Normalize(dy)};

                auto new_x{pos.x + norm_dx};
                auto new_y{pos.y + norm_dy};

                auto new_pos{Point{new_x, new_y}};

                if (new_pos == npc->GetDestination())
                {
                    npc->SetDestination({-1, -1});
                }

                auto tl{w_area->GetTile(new_pos.x, new_pos.y)};

                if (tl && !tl->GetNPC() && tl->GetGround() != Hash("ground_water"))
                {
                    auto old_pos{pos};

                    npc->SetTicksLastMovement(now);

                    auto old_tl{w_area->GetTile(old_pos.x, old_pos.y)};

                    auto new_tl{w_area->GetTile(new_pos.x, new_pos.y)};

                    old_tl->SetNPC(nullptr);

                    new_tl->SetNPC(npc);

                    npcs.erase(npc);

                    npcs.insert({npc, {new_pos.x, new_pos.y}});
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
            auto player_pos{_<PlayerCharacter>().GetPosition()};

            auto mouse_pos{GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow())};

            auto tl_sz{CalcTileSize()};

            auto screen_rel_x{CInt(mouse_pos.x / tl_sz.width)};

            auto grid_sz{CalcGridSize()};

            auto hovered_x_coord{player_pos.x - (grid_sz.width - 1) / 2 +
                                 screen_rel_x};

            auto screen_rel_x_px{
                (hovered_x_coord - (player_pos.x - (grid_sz.width - 1) / 2)) *
                tl_sz.width};

            auto w_area{_<World>().GetCurrentWorldArea()};

            auto extra_rows{8};

            auto top_y_coord{CInt(player_pos.y - (grid_sz.height - 1) / 2) -
                             extra_rows};

            auto player_tl{w_area->GetTile(player_pos)};

            auto player_elev{player_tl ? w_area->GetTile(player_pos)->GetElevation()
                                       : 0};

            auto screen_rel_y_px{-extra_rows * tl_sz.height};

            for (auto y = -extra_rows; y < grid_sz.height + extra_rows; y++)
            {
                auto y_coord{CInt(player_pos.y - (grid_sz.height - 1) / 2 + y)};

                auto coord{Point{hovered_x_coord, y_coord}};

                auto tl{w_area->GetTile(coord)};

                if (!tl)
                {
                    screen_rel_y_px = 0.5f +
                                      (y - (grid_sz.height - 1) / 2) * tl_sz.height +
                                      player_elev * tl_sz.height / 2;

                    continue;
                }

                auto elev{tl->GetElevation()};

                screen_rel_y_px = 0.5f + (y - (grid_sz.height - 1) / 2) * tl_sz.height +
                                  (player_elev - elev) * tl_sz.height / 2;

                auto coord_nw{Point{coord.x, coord.y}};

                auto coord_ne{Point{coord.x + 1, coord.y}};

                auto coord_sw{Point{coord.x, coord.y + 1}};

                auto coord_se{Point{coord.x + 1, coord.y + 1}};

                if (!w_area->IsValidCoordinate(coord_nw.x, coord_nw.y) ||
                    !w_area->IsValidCoordinate(coord_ne.x, coord_ne.y) ||
                    !w_area->IsValidCoordinate(coord_sw.x, coord_sw.y) ||
                    !w_area->IsValidCoordinate(coord_se.x, coord_se.y))
                {
                    continue;
                }

                auto tl_nw{w_area->GetTile(coord_nw)};
                auto tl_ne{w_area->GetTile(coord_ne)};
                auto tl_sw{w_area->GetTile(coord_sw)};
                auto tl_se{w_area->GetTile(coord_se)};

                if (!tl_nw || !tl_ne || !tl_se || !tl_sw)
                {
                    continue;
                }

                float local_tl_h;

                if (tl_nw->GetElevation() > tl_sw->GetElevation() &&
                    tl_ne->GetElevation() > tl_se->GetElevation())
                {
                    local_tl_h = tl_sz.height * 1.5f;
                }
                else if (tl_nw->GetElevation() < tl_sw->GetElevation() &&
                         tl_ne->GetElevation() < tl_se->GetElevation())
                {
                    local_tl_h = tl_sz.height * 0.5f;
                }
                else if (tl_ne->GetElevation() > tl_nw->GetElevation() &&
                         tl_se->GetElevation() > tl_sw->GetElevation())
                {
                    local_tl_h = tl_sz.height * 1.5f;
                }
                else if (tl_nw->GetElevation() > tl_ne->GetElevation() &&
                         tl_sw->GetElevation() > tl_se->GetElevation())
                {
                    local_tl_h = tl_sz.height * 1.5f;
                }
                else if (tl_nw->GetElevation() > tl_ne->GetElevation() &&
                         tl_nw->GetElevation() > tl_se->GetElevation() &&
                         tl_nw->GetElevation() > tl_sw->GetElevation())
                {
                    local_tl_h = tl_sz.height * 1.5f;
                }
                else if (tl_ne->GetElevation() > tl_nw->GetElevation() &&
                         tl_ne->GetElevation() > tl_se->GetElevation() &&
                         tl_ne->GetElevation() > tl_sw->GetElevation())
                {
                    local_tl_h = tl_sz.height * 1.5f;
                }
                else if (tl_sw->GetElevation() > tl_nw->GetElevation() &&
                         tl_sw->GetElevation() > tl_se->GetElevation() &&
                         tl_sw->GetElevation() > tl_ne->GetElevation())
                {
                    local_tl_h = tl_sz.height * 1.0f;
                }
                else if (tl_se->GetElevation() > tl_nw->GetElevation() &&
                         tl_se->GetElevation() > tl_ne->GetElevation() &&
                         tl_se->GetElevation() > tl_sw->GetElevation())
                {
                    local_tl_h = tl_sz.height * 1.0f;
                }
                else if (tl_sw->GetElevation() < tl_nw->GetElevation() &&
                         tl_sw->GetElevation() < tl_ne->GetElevation() &&
                         tl_sw->GetElevation() < tl_se->GetElevation())
                {
                    local_tl_h = tl_sz.height * 1.5f;
                }
                else if (tl_se->GetElevation() < tl_nw->GetElevation() &&
                         tl_se->GetElevation() < tl_ne->GetElevation() &&
                         tl_se->GetElevation() < tl_sw->GetElevation())
                {
                    local_tl_h = tl_sz.height * 1.5f;
                }
                else if (tl_nw->GetElevation() < tl_ne->GetElevation() &&
                         tl_nw->GetElevation() < tl_sw->GetElevation() &&
                         tl_nw->GetElevation() < tl_se->GetElevation())
                {
                    local_tl_h = tl_sz.height * 1.0f;
                }
                else if (tl_ne->GetElevation() < tl_nw->GetElevation() &&
                         tl_ne->GetElevation() < tl_sw->GetElevation() &&
                         tl_ne->GetElevation() < tl_se->GetElevation())
                {
                    local_tl_h = tl_sz.height * 1.0f;
                }
                else if (tl_sw->GetElevation() == tl_ne->GetElevation() &&
                         tl_nw->GetElevation() < tl_sw->GetElevation() &&
                         tl_se->GetElevation() < tl_sw->GetElevation())
                {
                    local_tl_h = tl_sz.height * 1.5f;
                }
                else if (tl_nw->GetElevation() == tl_se->GetElevation() &&
                         tl_ne->GetElevation() < tl_nw->GetElevation() &&
                         tl_sw->GetElevation() < tl_nw->GetElevation())
                {
                    local_tl_h = tl_sz.height * 1.5f;
                }
                else
                {
                    local_tl_h = tl_sz.height;
                }

                auto rect{RectF{screen_rel_x_px,
                                 screen_rel_y_px - local_tl_h / 2, tl_sz.width,
                                 local_tl_h}};

                if (rect.Contains(mouse_pos))
                {
                    m_hoveredCoordinate = {hovered_x_coord, y_coord};
                    
                    return;
                }
            }
        }
    }
}
_NS_END_