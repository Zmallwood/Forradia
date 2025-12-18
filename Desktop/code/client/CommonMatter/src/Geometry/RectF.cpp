/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "RectF.hpp"
#include "StdAfx.hpp"

namespace Forradia {
  auto RectF::Contains(PointF point) const -> bool {
    return point.x >= this->x && point.y >= this->y && point.x < this->x + this->width &&
           point.y < this->y + this->height;
  }

  auto RectF::GetPosition() const -> PointF {
    return {this->x, this->y};
  }

  auto RectF::Offset(PointF offset) -> void {
    this->x += offset.x;
    this->y += offset.y;
  }
}
