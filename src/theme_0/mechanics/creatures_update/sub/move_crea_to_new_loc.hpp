/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class creature;

  void move_crea_to_new_loc(s_ptr<creature> crea, point new_pos);
}