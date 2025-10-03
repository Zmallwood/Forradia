/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gen_new_world.hpp"
#include "sub/clear_with_dirt.hpp"
#include "sub/gen_creas.hpp"
#include "sub/gen_elev.hpp"
#include "sub/gen_grass.hpp"
#include "sub/gen_lakes.hpp"
#include "sub/gen_npcs.hpp"
#include "sub/gen_objs.hpp"
#include "sub/gen_rivers.hpp"
#include "sub/gen_rock.hpp"

namespace forr {
  void gen_new_world() {
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
}