/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class ImageRenderer {
  public:
    void DrawImage(StringView imageName, float x, float y, float width,
                   float height) const;

    void DrawImage(int imageNameHash, float x, float y, float width,
                   float height) const;

    void DrawImageWithAutoHeight(StringView imageName, float x, float y,
                                 float width) const;
  };
}