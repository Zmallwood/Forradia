/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "core/gui.hpp"
#include "theme_0/func/core_game_objects/sub/body_part_types.hpp"

namespace forr {
  class gui_label;

  class gui_player_body_window : public gui_window {
   public:
    gui_player_body_window()
        : gui_window(0.2f, 0.2f, 0.2f, 0.5f, "Player body") {
      init();
    }

   protected:
    void init();

   private:
    void sel_body_part(body_part_types type);

    void update_body_part_info_lbls();

    body_part_types m_sel_body_part{body_part_types::none};
    s_ptr<gui_label> m_lbl_body_part_name;
    s_ptr<gui_label> m_lbl_body_part_str;
    s_ptr<gui_label> m_lbl_body_part_energy;
    s_ptr<gui_label> m_lbl_body_part_temp;
  };
}