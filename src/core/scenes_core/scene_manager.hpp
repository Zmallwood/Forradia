/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class IScene;

  class SceneManager {
  public:
    void AddScene(str_view sceneName, IScene &scene);

    void GoToScene(str_view sceneName);

    void UpdateCurrentScene();

    void RenderCurrentScene() const;

  private:
    std::map<int, IScene &> m_scenes;
    int m_currentScene{0};
  };
}
