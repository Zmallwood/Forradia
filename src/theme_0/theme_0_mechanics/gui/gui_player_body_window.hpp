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
      Initialize();
    }

  protected:
    void Initialize();

  private:
    void SelectBodyPart(body_part_types bodyPartType);

    void UpdateBodyPartInformationLabels();

    body_part_types m_selectedBodyPart{body_part_types::None};
    s_ptr<gui_label> m_labelBodyPartName;
    s_ptr<gui_label> m_labelBodyPartStrength;
    s_ptr<gui_label> m_labelBodyPartEnergy;
    s_ptr<gui_label> m_labelBodyPartTemperature;
  };
}