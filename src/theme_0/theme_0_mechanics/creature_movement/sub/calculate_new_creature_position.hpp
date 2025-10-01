/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class creature;

  point CalculateNewCreaturePosition(s_ptr<creature> creature);
}