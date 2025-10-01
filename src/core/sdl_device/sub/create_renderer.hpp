/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  SharedPtr<SDL_Renderer> CreateRenderer(SharedPtr<SDL_Window> window);
}