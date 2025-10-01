/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  s_ptr<SDL_Renderer> create_renderer(s_ptr<SDL_Window> window);
}