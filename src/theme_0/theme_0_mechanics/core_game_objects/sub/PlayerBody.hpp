/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "BodyPart.hpp"
#include "BodyPartTypes.hpp"

namespace Forradia {
  class PlayerBody {
  public:
    PlayerBody() { Initialize(); }

    BodyPart *GetBodyPartPtr(BodyPartTypes bodyPartType);

  private:
    void Initialize();

    Map<BodyPartTypes, BodyPart> m_bodyParts;
  };
}