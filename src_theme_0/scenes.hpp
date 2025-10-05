/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "engine.hpp"

namespace forr {
  class gui_comp;

  class intro_scene : public i_scene {
   public:
    intro_scene() { setup_funcs(); }

   private:
    void setup_funcs();

    s_ptr<gui_comp> start_text_comp_;
  };

  class main_menu_scene : public i_scene {
   public:
    main_menu_scene() { setup_funcs(); }

   private:
    void setup_funcs();
  };

  class world_gen_scene : public i_scene {
   public:
    world_gen_scene() { setup_funcs(); }

   private:
    void setup_funcs();
  };

  class main_scene : public i_scene {
   public:
    main_scene() { setup_funcs(); }

   private:
    void setup_funcs();
  };
}