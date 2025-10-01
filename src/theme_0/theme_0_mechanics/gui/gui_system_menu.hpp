/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "core/gui_core/gui_component.hpp"

namespace forr {
  class gui_system_menu : public gui_component {
  public:
    gui_system_menu() : gui_component(0.0f, 0.0f, 1.0f, 1.0f) { Initialize(); }

  protected:
    void Initialize();

    virtual void UpdateDerived() override;

    virtual void RenderDerived() const override;
  };
}