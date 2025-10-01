/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class GUI;

  class IScene {
  public:
    void Initialize();

    void Update();

    void Render() const;

    void OnEnter();

  protected:
    virtual void InitializeDerived() {}

    virtual void OnEnterDerived() {}

    virtual void UpdateDerived() {}

    virtual void RenderDerived() const {}

    auto GetGUI() const { return m_gui; }

  private:
    s_ptr<GUI> m_gui;
  };
}
