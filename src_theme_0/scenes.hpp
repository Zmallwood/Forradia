/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "engine.hpp"

namespace forr {
  class gui_comp;

  class intro_scene : public i_scene {
   protected:
    void init_derived() override;

    void on_enter_derived() override;

    void update_derived() override;

    void render_derived() const override;

   private:
    s_ptr<gui_comp> start_text_comp_;
  };

  class main_menu_scene : public i_scene {
   protected:
    void init_derived() override;

    void update_derived() override;

    void render_derived() const override;
  };

  class world_gen_scene : public i_scene {
   protected:
    void on_enter_derived() override;
  };

  class main_scene : public i_scene {
   protected:
    void init_derived() override;

    void on_enter_derived() override;

    void update_derived() override;

    void render_derived() const override;
  };
}