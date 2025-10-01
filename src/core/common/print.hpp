/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  /**
   * \brief Print out a string of text, without a following line break.
   *
   * \param text Text to print.
   */
  void Print(str_view text);

  /**
   * \brief Print out a string of text, with an added line break at the end.
   *
   * \param text Text to print.
   */
  void PrintLine(str_view text);
}