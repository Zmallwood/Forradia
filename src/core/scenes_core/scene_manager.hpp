/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class i_scene;

  class scene_manager {
  public:
    void add_scene(str_view scene_name, i_scene &scene);

    void go_to_scene(str_view scene_name);

    void update_current_scene();

    void render_current_scene() const;

  private:
    std::map<int, i_scene &> m_scenes;
    int m_current_scene{0};
  };
}
