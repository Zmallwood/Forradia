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
void update_kb_actions()
{
    if (_<Core::engine::Input::kb_inp>().key_pressed_pick_res(SDLK_ESCAPE))
        _<gui_sys_menu>().toggle_visible();
    else if (_<Core::engine::Input::kb_inp>().key_pressed_pick_res(SDLK_c))
        _<gui_player_body_win>().toggle_visible();
    else if (_<Core::engine::Input::kb_inp>().key_pressed_pick_res(SDLK_b))
        _<gui_inventory_win>().toggle_visible();
}

void update_mouse_actions()
{
    if (_<Core::engine::Input::mouse_inp::right_mouse_btn>()
            .been_fired_pick_res())
    {
        _<gui_interact_menu>().build_menu();
        _<gui_interact_menu>().set_visible(true);
        _<gui_interact_menu>().set_pos(
            norm_mouse_pos(_<engine::sdl_device>().win()));
    }
}

void update_kb_movem()
{
    auto up_press{_<Core::engine::Input::kb_inp>().key_pressed(SDLK_UP)};
    auto right_press{_<Core::engine::Input::kb_inp>().key_pressed(SDLK_RIGHT)};
    auto down_press{_<Core::engine::Input::kb_inp>().key_pressed(SDLK_DOWN)};
    auto left_press{_<Core::engine::Input::kb_inp>().key_pressed(SDLK_LEFT)};
    auto w_press{_<Core::engine::Input::kb_inp>().key_pressed(SDLK_w)};
    auto a_press{_<Core::engine::Input::kb_inp>().key_pressed(SDLK_a)};
    auto s_press{_<Core::engine::Input::kb_inp>().key_pressed(SDLK_s)};
    auto d_press{_<Core::engine::Input::kb_inp>().key_pressed(SDLK_d)};
    if (up_press || right_press || down_press || left_press)
        _<player>().set_dest({-1, -1});
    auto now{ticks()};
    if (now >= _<player>().ticks_last_move() +
                   inv_movem_spd(_<player>().movem_spd()) &&
        (up_press || right_press || down_press || left_press || w_press ||
         a_press || s_press || d_press))
    {
        if (up_press || w_press)
            _<player>().move_n();
        if (right_press || d_press)
            _<player>().move_e();
        if (down_press || s_press)
            _<player>().move_s();
        if (left_press || a_press)
            _<player>().move_w();
        _<player>().set_ticks_last_move(now);
    }
}

void update_mouse_movem()
{
    if (_<Core::engine::Input::mouse_inp::left_mouse_btn>()
            .been_fired_pick_res())
    {
        auto new_dest{_<tl_hovering>().hovered_coord()};
        _<player>().set_dest(new_dest);
    }
    auto player_pos{_<player>().pos()};
    auto dest{_<player>().dest()};
    if (dest == pt{-1, -1})
        return;
    auto now{ticks()};
    if (now >=
        _<player>().ticks_last_move() + inv_movem_spd(_<player>().movem_spd()))
    {
        auto dx{dest.x - player_pos.x};
        auto dy{dest.y - player_pos.y};
        if (dx < 0)
            _<player>().move_w();
        if (dy < 0)
            _<player>().move_n();
        if (dx > 0)
            _<player>().move_e();
        if (dy > 0)
            _<player>().move_s();
        if (dest == player_pos)
            _<player>().set_dest({-1, -1});
        _<player>().set_ticks_last_move(now);
    }
}

void update_crea_movem()
{
    auto w_area{_<world>().curr_w_area()};
    auto &creas{w_area->creatures_mirror_ref()};
    auto now{ticks()};
    for (auto it = creas.begin(); it != creas.end();)
    {
        auto crea{it->first};
        auto pos{it->second};
        if (now < crea->ticks_last_move() + inv_movem_spd(crea->movem_spd()))
        {
            ++it;
            continue;
        }
        auto dest{crea->dest()};
        if (dest.x == -1 && dest.y == -1)
        {
            auto new_dest{pos.x + rand_int(11) - 5};
            auto new_destination_y{pos.y + rand_int(11) - 5};
            crea->set_dest({new_dest, new_destination_y});
        }
        auto w_area{_<world>().curr_w_area()};
        auto &creas{w_area->creatures_mirror_ref()};
        auto dx{crea->dest().x - pos.x};
        auto dy{crea->dest().y - pos.y};
        auto norm_dx{normalize(dx)};
        auto norm_dy{normalize(dy)};
        auto new_x{pos.x + norm_dx};
        auto new_y{pos.y + norm_dy};
        pt new_pos{new_x, new_y};
        if (new_pos == crea->dest())
            crea->set_dest({-1, -1});
        auto tl{w_area->get_tl(new_pos.x, new_pos.y)};
        if (tl && !tl->creature() && tl->ground() != hash("ground_water"))
        {
            auto old_pos{creas.at(crea)};
            crea->set_ticks_last_move(now);
            auto old_tile{w_area->get_tl(old_pos.x, old_pos.y)};
            auto new_tile{w_area->get_tl(new_pos.x, new_pos.y)};
            old_tile->set_creature(nullptr);
            new_tile->set_creature(crea);
            creas.erase(crea);
            creas.insert({crea, {new_pos.x, new_pos.y}});
        }
        else
        {
            crea->set_dest({-1, -1});
        }
        ++it;
    }
}

void update_npcs()
{
    auto w_area{_<world>().curr_w_area()};
    auto &npcs{w_area->npcs_mirror_ref()};
    auto now{ticks()};
    for (auto it = npcs.begin(); it != npcs.end();)
    {
        auto npc{it->first};
        auto pos{it->second};
        if (now > npc->ticks_next_spontaneous_speech())
        {
            auto name{npc->name()};
            if (rand_int(20) == 0)
                _<gui_chat_box>().print(name +
                                        ": Buying blueberries, one gold each.");
            else
                _<gui_chat_box>().print(name + ": Hello all!");
            npc->set_ticks_next_spontaneous_speech(now + 5 * k_one_sec_millis +
                                                   (6000 * k_one_sec_millis));
        }
        if (now < npc->ticks_last_move() + inv_movem_spd(npc->movem_spd()))
        {
            ++it;
            continue;
        }
        auto dest{npc->dest()};
        if (dest.x == -1 && dest.y == -1)
        {
            auto new_dest_x{pos.x + rand_int(11) - 5};
            auto new_dest_y{pos.y + rand_int(11) - 5};
            npc->set_dest({new_dest_x, new_dest_y});
        }
        auto dx{npc->dest().x - pos.x};
        auto dy{npc->dest().y - pos.y};
        auto norm_dx{normalize(dx)};
        auto norm_dy{normalize(dy)};
        auto new_x{pos.x + norm_dx};
        auto new_y{pos.y + norm_dy};
        auto new_pos{pt{new_x, new_y}};
        if (new_pos == npc->dest())
            npc->set_dest({-1, -1});
        auto tl{w_area->get_tl(new_pos.x, new_pos.y)};
        if (tl && !tl->npc() && tl->ground() != hash("ground_water"))
        {
            auto old_pos{pos};
            npc->set_ticks_last_move(now);
            auto old_tl{w_area->get_tl(old_pos.x, old_pos.y)};
            auto new_tl{w_area->get_tl(new_pos.x, new_pos.y)};
            old_tl->set_npc(nullptr);
            new_tl->set_npc(npc);
            npcs.erase(npc);
            npcs.insert({npc, {new_pos.x, new_pos.y}});
        }
        else
        {
            npc->set_dest({-1, -1});
        }
        ++it;
    }
}

void tl_hovering::update()
{
    auto player_pos{_<player>().pos()};
    auto mouse_pos{norm_mouse_pos(_<engine::sdl_device>().win())};
    auto tl_sz{calc_tl_sz()};
    auto screen_rel_x{c_int(mouse_pos.x / tl_sz.w)};
    auto grid_sz{calc_grid_sz()};
    auto hovered_x_coord{player_pos.x - (grid_sz.w - 1) / 2 + screen_rel_x};
    auto screen_rel_x_px{
        (hovered_x_coord - (player_pos.x - (grid_sz.w - 1) / 2)) * tl_sz.w};
    auto w_area{_<world>().curr_w_area()};
    auto extra_rows{8};
    auto top_y_coord{c_int(player_pos.y - (grid_sz.h - 1) / 2) - extra_rows};
    auto player_tl{w_area->get_tl(player_pos)};
    auto player_elev{player_tl ? w_area->get_tl(player_pos)->elev() : 0};
    auto screen_rel_y_px{-extra_rows * tl_sz.h};
    for (auto y = -extra_rows; y < grid_sz.h + extra_rows; y++)
    {
        auto y_coord{c_int(player_pos.y - (grid_sz.h - 1) / 2 + y)};
        auto coord{pt{hovered_x_coord, y_coord}};
        auto tl{w_area->get_tl(coord)};
        if (!tl)
        {
            screen_rel_y_px = 0.5f + (y - (grid_sz.h - 1) / 2) * tl_sz.h +
                              player_elev * tl_sz.h / 2;
            continue;
        }
        auto elev{tl->elev()};
        screen_rel_y_px = 0.5f + (y - (grid_sz.h - 1) / 2) * tl_sz.h +
                          (player_elev - elev) * tl_sz.h / 2;
        auto coord_nw{pt{coord.x, coord.y}};
        auto coord_ne{pt{coord.x + 1, coord.y}};
        auto coord_sw{pt{coord.x, coord.y + 1}};
        auto coord_se{pt{coord.x + 1, coord.y + 1}};
        if (!w_area->is_valid_coord(coord_nw.x, coord_nw.y) ||
            !w_area->is_valid_coord(coord_ne.x, coord_ne.y) ||
            !w_area->is_valid_coord(coord_sw.x, coord_sw.y) ||
            !w_area->is_valid_coord(coord_se.x, coord_se.y))
        {
            continue;
        }
        auto tl_nw{w_area->get_tl(coord_nw)};
        auto tl_ne{w_area->get_tl(coord_ne)};
        auto tl_sw{w_area->get_tl(coord_sw)};
        auto tl_se{w_area->get_tl(coord_se)};
        if (!tl_nw || !tl_ne || !tl_se || !tl_sw)
            continue;
        float local_tl_h;
        if (tl_nw->elev() > tl_sw->elev() && tl_ne->elev() > tl_se->elev())
            local_tl_h = tl_sz.h * 1.5f;
        else if (tl_nw->elev() < tl_sw->elev() && tl_ne->elev() < tl_se->elev())
            local_tl_h = tl_sz.h * 0.5f;
        else if (tl_ne->elev() > tl_nw->elev() && tl_se->elev() > tl_sw->elev())
            local_tl_h = tl_sz.h * 1.5f;
        else if (tl_nw->elev() > tl_ne->elev() && tl_sw->elev() > tl_se->elev())
            local_tl_h = tl_sz.h * 1.5f;
        else if (tl_nw->elev() > tl_ne->elev() &&
                 tl_nw->elev() > tl_se->elev() && tl_nw->elev() > tl_sw->elev())
            local_tl_h = tl_sz.h * 1.5f;
        else if (tl_ne->elev() > tl_nw->elev() &&
                 tl_ne->elev() > tl_se->elev() && tl_ne->elev() > tl_sw->elev())
            local_tl_h = tl_sz.h * 1.5f;
        else if (tl_sw->elev() > tl_nw->elev() &&
                 tl_sw->elev() > tl_se->elev() && tl_sw->elev() > tl_ne->elev())
            local_tl_h = tl_sz.h * 1.0f;
        else if (tl_se->elev() > tl_nw->elev() &&
                 tl_se->elev() > tl_ne->elev() && tl_se->elev() > tl_sw->elev())
            local_tl_h = tl_sz.h * 1.0f;
        else if (tl_sw->elev() < tl_nw->elev() &&
                 tl_sw->elev() < tl_ne->elev() && tl_sw->elev() < tl_se->elev())
            local_tl_h = tl_sz.h * 1.5f;
        else if (tl_se->elev() < tl_nw->elev() &&
                 tl_se->elev() < tl_ne->elev() && tl_se->elev() < tl_sw->elev())
            local_tl_h = tl_sz.h * 1.5f;
        else if (tl_nw->elev() < tl_ne->elev() &&
                 tl_nw->elev() < tl_sw->elev() && tl_nw->elev() < tl_se->elev())
            local_tl_h = tl_sz.h * 1.0f;
        else if (tl_ne->elev() < tl_nw->elev() &&
                 tl_ne->elev() < tl_sw->elev() && tl_ne->elev() < tl_se->elev())
            local_tl_h = tl_sz.h * 1.0f;
        else if (tl_sw->elev() == tl_ne->elev() &&
                 tl_nw->elev() < tl_sw->elev() && tl_se->elev() < tl_sw->elev())
            local_tl_h = tl_sz.h * 1.5f;
        else if (tl_nw->elev() == tl_se->elev() &&
                 tl_ne->elev() < tl_nw->elev() && tl_sw->elev() < tl_nw->elev())
            local_tl_h = tl_sz.h * 1.5f;
        else
            local_tl_h = tl_sz.h;
        auto rect{rect_f{screen_rel_x_px, screen_rel_y_px - local_tl_h / 2,
                         tl_sz.w, local_tl_h}};
        if (rect.contains(mouse_pos))
        {
            hovered_coord_ = {hovered_x_coord, y_coord};
            return;
        }
    }
}
_NS_END_