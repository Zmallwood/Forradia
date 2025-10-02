/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "core/gui_core/windows/gui_window.hpp"
#include "theme_0/theme_0_mechanics/core_game_objects/sub/body_part_types.hpp"

namespace forr {
  class gui_label;

  class gui_player_body_window : public gui_window {
  public:
    gui_player_body_window()
        : gui_window(0.2f, 0.2f, 0.2f, 0.5f, "Player body") {
      initialize();
    }

  protected:
    void initialize();

  private:
    void select_body_part(body_part_types body_part_type);

    void update_body_part_information_labels();

    body_part_types m_selected_body_part{body_part_types::none};
    s_ptr<gui_label> m_label_body_part_name;
    s_ptr<gui_label> m_label_body_part_strength;
    s_ptr<gui_label> m_label_body_part_energy;
    s_ptr<gui_label> m_label_body_part_temperature;
  };
}