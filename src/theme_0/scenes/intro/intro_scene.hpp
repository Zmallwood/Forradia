/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "core/scenes_core.hpp"

namespace forr {
  class gui_component;

  class intro_scene : public i_scene {
  protected:
    void initialize_derived() override;

    void on_enter_derived() override;

    void update_derived() override;

    void render_derived() const override;

  private:
    s_ptr<gui_component> m_start_text;
  };
}
