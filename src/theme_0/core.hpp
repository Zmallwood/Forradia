/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "engine.hpp"

namespace forr {
  void run_new_theme_0();

  class gui_component;

  class intro_scene : public i_scene {
   protected:
    void init_derived() override;

    void on_enter_derived() override;

    void update_derived() override;

    void render_derived() const override;

   private:
    s_ptr<gui_component> m_start_text;
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