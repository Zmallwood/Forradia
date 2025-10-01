/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "core/gui_core/windows/gui_window.hpp"
#include "theme_0/theme_0_mechanics/core_game_objects/sub/body_part_types.hpp"

namespace forr {
  class GUILabel;

  class GUIPlayerBodyWindow : public GUIWindow {
  public:
    GUIPlayerBodyWindow() : GUIWindow(0.2f, 0.2f, 0.2f, 0.5f, "Player body") {
      Initialize();
    }

  protected:
    void Initialize();

  private:
    void SelectBodyPart(BodyPartTypes bodyPartType);

    void UpdateBodyPartInformationLabels();

    BodyPartTypes m_selectedBodyPart{BodyPartTypes::None};
    s_ptr<GUILabel> m_labelBodyPartName;
    s_ptr<GUILabel> m_labelBodyPartStrength;
    s_ptr<GUILabel> m_labelBodyPartEnergy;
    s_ptr<GUILabel> m_labelBodyPartTemperature;
  };
}