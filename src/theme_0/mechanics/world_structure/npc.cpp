/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "npc.hpp"

namespace forr {
  void npc::initialize() {
    generate_name();

    m_ticks_next_spontaneous_speech =
        get_ticks() + random_int(300 * k_one_second_millis);
  }

  void npc::generate_name() {
    vec<char> vowels{'a', 'e', 'i', 'o', 'u', 'y'};
    vec<char> consonants{'q', 'w', 'r', 't', 'p', 's', 'd', 'f', 'g', 'h',
                         'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm'};
    char c0{vowels.at(random_int(vowels.size()))};
    char c1{consonants.at(random_int(consonants.size()))};
    char c2{consonants.at(random_int(consonants.size()))};
    char c3{vowels.at(random_int(vowels.size()))};
    char c4{consonants.at(random_int(consonants.size()))};
    char c5{consonants.at(random_int(consonants.size()))};
    char c6{vowels.at(random_int(vowels.size()))};

    m_name = str() + c0 + c1 + c2 + c3 + c4 + c5 + c6;
  }
}