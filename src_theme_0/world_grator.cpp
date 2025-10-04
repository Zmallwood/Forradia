/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "world_grator.hpp"
#include "game_props.hpp"
#include "world_struct.hpp"

namespace forr {
  void world_grator::gen_new_world() {
    prep();
    clear_with_dirt();
    gen_grass();
    gen_lakes();
    gen_elev();
    gen_rock();
    gen_rivers();
    gen_objs();
    gen_creas();
    gen_npcs();
  }

  void world_grator::prep() {
    w_area_ = _<world>().curr_w_area();
    scale_ = _<game_props>().k_world_scaling;
    sz_ = w_area_->get_sz();
  }

  void world_grator::clear_with_dirt() const {
    for (auto y = 0; y < sz_.h; y++) {
      for (auto x = 0; x < sz_.w; x++) {
        auto tl{w_area_->get_tl(x, y)};
        if (tl) {
          tl->set_ground("GroundDirt");
        }
      }
    }
  }

  void world_grator::gen_grass() const {
    auto num_grass_areas{50 + rand_int(20)};
    for (auto i = 0; i < num_grass_areas; i++) {
      auto x_cent{rand_int(sz_.w)};
      auto y_cent{rand_int(sz_.h)};
      auto r{3 * scale_ + rand_int(10 * scale_)};
      for (auto y = y_cent - r; y <= y_cent + r; y++) {
        for (auto x = x_cent - r; x <= x_cent + r; x++) {
          if (!w_area_->is_valid_coord(x, y)) {
            continue;
          }
          auto dx{x - x_cent};
          auto dy{y - y_cent};
          if (dx * dx + dy * dy <= r * r) {
            auto tl{w_area_->get_tl(x, y)};
            tl->set_ground("GroundGrass");
          }
        }
      }
    }
  }

  void world_grator::gen_single_lake(int min_x, int min_y, int max_x, int max_y,
                                     int recurs) const {
    if (recurs == 0) {
      return;
    }
    auto x_cent{min_x + rand_int(max_x - min_x)};
    auto y_cent{min_y + rand_int(max_y - min_y)};
    auto max_r{c_int(3 * scale_ + rand_int(5 * scale_))};
    for (auto r = max_r; r >= 0; r--) {
      for (auto y = y_cent - r; y <= y_cent + r; y++) {
        for (auto x = x_cent - r; x <= x_cent + r; x++) {
          auto dx{x - x_cent};
          auto dy{y - y_cent};
          if (dx * dx + dy * dy <= r * r) {
            auto tl{w_area_->get_tl(x, y)};
            if (tl) {
              pt n{x, y - 1};
              pt e{x + 1, y};
              pt s{x, y + 1};
              pt w{x - 1, y};
              pt nw{x - 1, y - 1};
              pt ne{x + 1, y - 1};
              pt se{x + 1, y + 1};
              pt sw{x - 1, y + 1};
              pt nn{x, y - 2};
              pt ww{x - 2, y};
              pt ee{x + 2, y};
              pt ss{x, y + 2};
              pt nwnw{x - 2, y - 2};
              pt nene{x + 2, y - 2};
              pt sese{x + 2, y + 2};
              pt swsw{x - 2, y + 2};
              auto tl_n{w_area_->get_tl(n)};
              auto tl_e{w_area_->get_tl(e)};
              auto tl_s{w_area_->get_tl(s)};
              auto tl_w{w_area_->get_tl(w)};
              auto tl_nw{w_area_->get_tl(nw)};
              auto tl_ne{w_area_->get_tl(ne)};
              auto tl_se{w_area_->get_tl(se)};
              auto tl_sw{w_area_->get_tl(sw)};
              auto tl_nn{w_area_->get_tl(nn)};
              auto tl_ww{w_area_->get_tl(ww)};
              auto tl_ee{w_area_->get_tl(ee)};
              auto tl_ss{w_area_->get_tl(ss)};
              auto tl_nwnw{w_area_->get_tl(nwnw)};
              auto tl_nene{w_area_->get_tl(nene)};
              auto tl_sese{w_area_->get_tl(sese)};
              auto tl_swsw{w_area_->get_tl(swsw)};
              auto elev_n{tl_n ? tl_n->elev() : 0};
              auto elev_e{tl_e ? tl_e->elev() : 0};
              auto elev_s{tl_s ? tl_s->elev() : 0};
              auto elev_w{tl_w ? tl_w->elev() : 0};
              auto elev_nw{tl_nw ? tl_nw->elev() : 0};
              auto elev_ne{tl_ne ? tl_ne->elev() : 0};
              auto elev_se{tl_se ? tl_se->elev() : 0};
              auto elev_sw{tl_sw ? tl_sw->elev() : 0};
              auto elev_nn{tl_nn ? tl_nn->elev() : 0};
              auto elev_ww{tl_ww ? tl_ww->elev() : 0};
              auto elev_ee{tl_ee ? tl_ee->elev() : 0};
              auto elev_ss{tl_ss ? tl_ss->elev() : 0};
              auto elev_nwnw{tl_nwnw ? tl_nwnw->elev() : 0};
              auto elev_nene{tl_nene ? tl_nene->elev() : 0};
              auto elev_sese{tl_sese ? tl_sese->elev() : 0};
              auto elev_swsw{tl_swsw ? tl_swsw->elev() : 0};
              if (elev_n == 0 && elev_e == 0 && elev_s == 0 && elev_w == 0 &&
                  elev_nw == 0 && elev_ne == 0 && elev_se == 0 &&
                  elev_sw == 0 && elev_nn == 0 && elev_ww == 0 &&
                  elev_ee == 0 && elev_ss == 0 && elev_nwnw == 0 &&
                  elev_nene == 0 && elev_sese == 0 && elev_swsw == 0) {
                tl->set_ground("GroundWater");
              }
              tl->set_water_depth(tl->water_depth() + 1);
            }
          }
        }
      }
    }
    gen_single_lake(x_cent - max_r, y_cent - max_r, x_cent + max_r,
                    y_cent + max_r, recurs - 1);
  }

  void world_grator::gen_lakes() const {
    auto num_lakes{20 + rand_int(5)};
    for (auto i = 0; i < num_lakes; i++) {
      gen_single_lake(0, 0, sz_.w, sz_.h, 2 + rand_int(5));
    }
  }

  void world_grator::gen_elev() const {
    auto num_hills{140 + rand_int(30)};
    for (auto i = 0; i < num_hills; i++) {
      auto x_cent{rand_int(sz_.w)};
      auto y_cent{rand_int(sz_.h)};
      auto max_r{5 * scale_ + rand_int(5 * scale_)};
      for (auto r = max_r; r >= 0; r--) {
        for (auto y = y_cent - r; y <= y_cent + r; y++) {
          for (auto x = x_cent - r; x <= x_cent + r; x++) {
            if (!w_area_->is_valid_coord(x, y)) {
              continue;
            }
            auto dx{x - x_cent};
            auto dy{y - y_cent};
            if (dx * dx + dy * dy <= r * r) {
              auto tl{w_area_->get_tl(x, y)};
              if (tl && tl->ground() != hash("GroundWater")) {
                auto tl_n{w_area_->get_tl(x, y - 1)};
                auto tl_s{w_area_->get_tl(x, y + 1)};
                auto tl_w{w_area_->get_tl(x - 1, y)};
                auto tl_e{w_area_->get_tl(x + 1, y)};
                auto tl_nw{w_area_->get_tl(x - 1, y - 1)};
                auto tl_ne{w_area_->get_tl(x + 1, y - 1)};
                auto tl_sw{w_area_->get_tl(x - 1, y + 1)};
                auto tl_se{w_area_->get_tl(x + 1, y + 1)};
                if ((tl_n && tl_n->ground() == hash("GroundWater")) ||
                    (tl_s && tl_s->ground() == hash("GroundWater")) ||
                    (tl_w && tl_w->ground() == hash("GroundWater")) ||
                    (tl_e && tl_e->ground() == hash("GroundWater")) ||
                    (tl_nw && tl_nw->ground() == hash("GroundWater")) ||
                    (tl_ne && tl_ne->ground() == hash("GroundWater")) ||
                    (tl_sw && tl_sw->ground() == hash("GroundWater")) ||
                    (tl_se && tl_se->ground() == hash("GroundWater"))) {
                  continue;
                }
                if (tl_n && tl_n->elev() < tl->elev()) {
                  continue;
                }
                if (tl_s && tl_s->elev() < tl->elev()) {
                  continue;
                }
                if (tl_w && tl_w->elev() < tl->elev()) {
                  continue;
                }
                if (tl_e && tl_e->elev() < tl->elev()) {
                  continue;
                }
                if (tl_nw && tl_nw->elev() < tl->elev()) {
                  continue;
                }
                if (tl_ne && tl_ne->elev() < tl->elev()) {
                  continue;
                }
                if (tl_sw && tl_sw->elev() < tl->elev()) {
                  continue;
                }
                if (tl_se && tl_se->elev() < tl->elev()) {
                  continue;
                }
                tl->set_elev(tl->elev() + 1);
              }
            }
          }
        }
      }
    }
  }

  void world_grator::gen_rock() const {
    auto num_rock_areas{30 + rand_int(10)};
    for (auto i = 0; i < num_rock_areas; i++) {
      auto x_center{rand_int(sz_.w)};
      auto y_center{rand_int(sz_.h)};
      auto r{3 * scale_ + rand_int(10 * scale_)};
      for (auto y = y_center - r; y <= y_center + r; y++) {
        for (auto x = x_center - r; x <= x_center + r; x++) {
          if (!w_area_->is_valid_coord(x, y)) {
            continue;
          }
          auto dx{x - x_center};
          auto dy{y - y_center};
          if (dx * dx + dy * dy <= r * r) {
            auto tl{w_area_->get_tl(x, y)};
            if (tl->elev() > 0) {
              tl->set_ground("GroundRock");
            }
          }
        }
      }
    }
  }

  void world_grator::gen_rivers() const {
    auto num_rivers{20 * scale_ + rand_int(5 * scale_)};
    for (auto i = 0; i < num_rivers; i++) {
      auto x{c_float(rand_int(sz_.w))};
      auto y{c_float(rand_int(sz_.h))};
      auto start_angle{rand_int(360)};
      auto len{45 + rand_int(20)};
      auto prev_x_coord{-1};
      auto prev_y_coord{-1};
      s_ptr<tile> prev_tl;
      for (auto j = 0; j < len; j++) {
        auto angle{start_angle + std::sin(j * M_PI / 10.0f) * 45};
        auto x_coord{c_int(x)};
        auto y_coord{c_int(y)};
        if (!w_area_->is_valid_coord(x_coord, y_coord)) {
          continue;
        }
        auto tl = w_area_->get_tl(x_coord, y_coord);
        if (tl && prev_tl) {
          // tile->SetGround("GroundWater");
          if (x_coord == prev_x_coord && y_coord > prev_y_coord) {
            prev_tl->set_river_dir_1(dirs::s);
            tl->set_river_dir_2(dirs::n);
          } else if (x_coord == prev_x_coord && y_coord < prev_y_coord) {
            prev_tl->set_river_dir_1(dirs::n);
            tl->set_river_dir_2(dirs::s);
          } else if (y_coord == prev_y_coord && x_coord > prev_x_coord) {
            prev_tl->set_river_dir_1(dirs::e);
            tl->set_river_dir_2(dirs::w);
          } else if (y_coord == prev_y_coord && x_coord < prev_x_coord) {
            prev_tl->set_river_dir_1(dirs::w);
            tl->set_river_dir_2(dirs::e);
          } else if (y_coord < prev_y_coord && x_coord > prev_x_coord) {
            prev_tl->set_river_dir_1(dirs::ne);
            tl->set_river_dir_2(dirs::sw);
          } else if (y_coord > prev_y_coord && x_coord > prev_x_coord) {
            prev_tl->set_river_dir_1(dirs::se);
            tl->set_river_dir_2(dirs::nw);
          } else if (y_coord < prev_y_coord && x_coord < prev_x_coord) {
            prev_tl->set_river_dir_1(dirs::nw);
            tl->set_river_dir_2(dirs::se);
          } else if (y_coord > prev_y_coord && x_coord < prev_x_coord) {
            prev_tl->set_river_dir_1(dirs::sw);
            tl->set_river_dir_2(dirs::ne);
          }
        }
        auto dx = std::cos(angle * M_PI / 180.0f);
        auto dy = std::sin(angle * M_PI / 180.0f);
        x += dx;
        y += dy;
        prev_x_coord = x_coord;
        prev_y_coord = y_coord;
        prev_tl = tl;
      }
    }
  }

  void world_grator::gen_objs() const {
    auto num_fir_trees{1000 * scale_ + rand_int(50)};
    for (auto i = 0; i < num_fir_trees; i++) {
      auto x{rand_int(sz_.w)};
      auto y{rand_int(sz_.h)};
      auto tl{w_area_->get_tl(x, y)};
      if (tl && tl->ground() != hash("GroundWater") &&
          tl->ground() != hash("GroundRock")) {
        tl->objects_stack()->clear_objs();
        tl->objects_stack()->add_tree_obj("ObjectFirTree");
      }
    }
    auto num_birch_trees{1000 * scale_ + rand_int(50)};
    for (auto i = 0; i < num_birch_trees; i++) {
      auto x{rand_int(sz_.w)};
      auto y{rand_int(sz_.h)};
      auto tl{w_area_->get_tl(x, y)};
      if (tl && tl->ground() != hash("GroundWater") &&
          tl->ground() != hash("GroundRock")) {
        tl->objects_stack()->clear_objs();
        tl->objects_stack()->add_tree_obj("ObjectBirchTree");
      }
    }
    auto num_bush_1s{400 * scale_ + rand_int(100)};
    for (auto i = 0; i < num_bush_1s; i++) {
      auto x{rand_int(sz_.w)};
      auto y{rand_int(sz_.h)};
      auto tl{w_area_->get_tl(x, y)};
      if (tl && tl->ground() != hash("GroundWater") &&
          tl->ground() != hash("GroundRock")) {
        tl->objects_stack()->clear_objs();
        tl->objects_stack()->add_obj("ObjectBush1");
      }
    }
    auto num_bush_2s{400 * scale_ + rand_int(100)};
    for (auto i = 0; i < num_bush_2s; i++) {
      auto x{rand_int(sz_.w)};
      auto y{rand_int(sz_.h)};
      auto tl{w_area_->get_tl(x, y)};
      if (tl && tl->ground() != hash("GroundWater") &&
          tl->ground() != hash("GroundRock")) {
        tl->objects_stack()->clear_objs();
        tl->objects_stack()->add_obj("ObjectBush2");
      }
    }
    auto num_pink_flowers{400 * scale_ + rand_int(100)};
    for (auto i = 0; i < num_pink_flowers; i++) {
      auto x{rand_int(sz_.w)};
      auto y{rand_int(sz_.h)};
      auto tl{w_area_->get_tl(x, y)};
      if (tl && tl->ground() != hash("GroundWater") &&
          tl->ground() != hash("GroundRock")) {
        tl->objects_stack()->clear_objs();
        tl->objects_stack()->add_obj("ObjectPinkFlower");
      }
    }
    auto num_tall_grasses{400 * scale_ + rand_int(100)};
    for (auto i = 0; i < num_tall_grasses; i++) {
      auto x{rand_int(sz_.w)};
      auto y{rand_int(sz_.h)};
      auto tl{w_area_->get_tl(x, y)};
      if (tl && tl->ground() != hash("GroundWater") &&
          tl->ground() != hash("GroundRock")) {
        tl->objects_stack()->clear_objs();
        tl->objects_stack()->add_obj("ObjectTallGrass");
      }
    }
    auto num_stone_boulders{200 * scale_ + rand_int(100)};
    for (auto i = 0; i < num_stone_boulders; i++) {
      auto x{rand_int(sz_.w)};
      auto y{rand_int(sz_.h)};
      auto tl{w_area_->get_tl(x, y)};
      if (tl && tl->water_depth() < 4) {
        tl->objects_stack()->clear_objs();
        tl->objects_stack()->add_obj("ObjectStoneBoulder");
      }
    }
  }

  void world_grator::gen_creas() const {
    auto num_rats{200 * scale_ + rand_int(15 * scale_)};
    for (auto i = 0; i < num_rats; i++) {
      auto x{rand_int(sz_.w)};
      auto y{rand_int(sz_.h)};
      auto tl{w_area_->get_tl(x, y)};
      if (tl && !tl->creature() && tl->ground() != hash("GroundWater")) {
        auto new_crea = std::make_shared<creature>("CreatureRat");
        tl->set_creature(new_crea);
        w_area_->creatures_mirror_ref().insert({tl->creature(), {x, y}});
      }
    }
    auto num_butterflies{200 * scale_ + rand_int(15 * scale_)};
    for (auto i = 0; i < num_butterflies; i++) {
      auto x{rand_int(sz_.w)};
      auto y{rand_int(sz_.h)};
      auto tl{w_area_->get_tl(x, y)};
      if (tl && !tl->creature() && tl->ground() != hash("GroundWater")) {
        auto new_crea = std::make_shared<creature>("CreatureButterfly");
        tl->set_creature(new_crea);
        w_area_->creatures_mirror_ref().insert({tl->creature(), {x, y}});
      }
    }
  }

  void world_grator::gen_npcs() const {
    auto num_npc_0s{200 * scale_ + rand_int(15 * scale_)};
    for (auto i = 0; i < num_npc_0s; i++) {
      auto x{rand_int(sz_.w)};
      auto y{rand_int(sz_.h)};
      auto tl{w_area_->get_tl(x, y)};
      if (tl && !tl->npc() && tl->ground() != hash("GroundWater")) {
        auto new_npc = std::make_shared<npc>("NPC0");
        tl->set_npc(new_npc);
        w_area_->npcs_mirror_ref().insert({tl->npc(), {x, y}});
      }
    }
  }
}