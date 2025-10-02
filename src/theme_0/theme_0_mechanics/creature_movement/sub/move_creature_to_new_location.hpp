/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class creature;

  void move_creature_to_new_location(s_ptr<creature> creature,
                                     point newPosition);
}