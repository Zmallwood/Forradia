/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  std::map<int, s_ptr<SDL_Texture>>
  get_loaded_images(str_view relative_images_path);
}