//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "NPC.hpp"

namespace Forradia::Theme0
{
    void NPC::Initialize()
    {
        this->GenerateName();

        m_ticksNextSpontaneousSpeech =
            GetTicks() + GetRandomInt(300 * k_oneSecMillis);
    }

    void NPC::GenerateName()
    {
        Vector<char> vowels{'a', 'e', 'i', 'o', 'u', 'y'};

        Vector<char> consonants{'q', 'w', 'r', 't', 'p',
                                's', 'd', 'f', 'g', 'h',
                                'j', 'k', 'l', 'z', 'x',
                                'c', 'v', 'b', 'n', 'm'};

        char c0{vowels.at(GetRandomInt(vowels.size()))};

        char c1{
            consonants.at(GetRandomInt(consonants.size()))};

        char c2{
            consonants.at(GetRandomInt(consonants.size()))};

        char c3{vowels.at(GetRandomInt(vowels.size()))};

        char c4{
            consonants.at(GetRandomInt(consonants.size()))};

        char c5{
            consonants.at(GetRandomInt(consonants.size()))};

        char c6{vowels.at(GetRandomInt(vowels.size()))};

        m_name =
            String() + c0 + c1 + c2 + c3 + c4 + c5 + c6;
    }
}