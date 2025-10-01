/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class Creature;

  void MoveCreatureToNewLocation(s_ptr<Creature> creature,
                                 Point newPosition);
}