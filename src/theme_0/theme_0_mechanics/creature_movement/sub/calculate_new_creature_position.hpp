/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class Creature;

  Point CalculateNewCreaturePosition(s_ptr<Creature> creature);
}