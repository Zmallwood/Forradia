/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class i_scene;

  class scene_manager {
  public:
    void AddScene(str_view sceneName, i_scene &scene);

    void GoToScene(str_view sceneName);

    void UpdateCurrentScene();

    void RenderCurrentScene() const;

  private:
    std::map<int, i_scene &> m_scenes;
    int m_currentScene{0};
  };
}
