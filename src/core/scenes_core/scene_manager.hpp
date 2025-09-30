/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia {
  class IScene;

  class SceneManager {
  public:
    void AddScene(StringView sceneName, IScene &scene);

    void GoToScene(StringView sceneName);

    void UpdateCurrentScene();

    void RenderCurrentScene() const;

  private:
    Map<int, IScene &> m_scenes;
    int m_currentScene{0};
  };
}
