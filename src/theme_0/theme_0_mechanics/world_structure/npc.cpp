/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "npc.hpp"

namespace forr {
  void npc::initialize() { generate_name(); }

  void npc::generate_name() {
    vec<char> vowels{'a', 'e', 'i', 'o', 'u', 'y'};
    vec<char> consonants{'q', 'w', 'r', 't', 'p', 's', 'd', 'f', 'g', 'h',
                         'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm'};
    char c0{vowels.at(random_int(vowels.size() + 1))};
    char c1{consonants.at(random_int(consonants.size() + 1))};
    char c2{consonants.at(random_int(consonants.size() + 1))};
    char c3{vowels.at(random_int(vowels.size() + 1))};
    char c4{consonants.at(random_int(consonants.size() + 1))};
    char c5{consonants.at(random_int(consonants.size() + 1))};
    char c6{vowels.at(random_int(vowels.size() + 1))};
  }
}