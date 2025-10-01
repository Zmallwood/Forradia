/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "directions.hpp"

namespace forr {
  class ObjectsStack;
  class Creature;

  class Tile {
  public:
    Tile() { Initialize(); }

    void SetGround(StringView groundName);

    auto GetGround() const { return m_ground; }

    auto GetObjectsStack() const { return m_objectsStack; }

    auto GetCreature() const { return m_creature; }

    void SetCreature(SharedPtr<Creature> value) { m_creature = value; }

    auto GetElevation() const { return m_elevation; }

    void SetElevation(int value) { m_elevation = value; }

    auto GetWaterDepth() const { return m_waterDepth; }

    void SetWaterDepth(int value) { m_waterDepth = value; }

    auto GetRiverDirection1() const { return m_riverDirection1; }

    void SetRiverDirection1(Directions value) { m_riverDirection1 = value; }

    auto GetRiverDirection2() const { return m_riverDirection2; }

    void SetRiverDirection2(Directions value) { m_riverDirection2 = value; }

  private:
    void Initialize();

    int m_ground{0};
    SharedPtr<ObjectsStack> m_objectsStack;
    SharedPtr<Creature> m_creature;
    int m_elevation{0};
    int m_waterDepth{0};
    Directions m_riverDirection1{Directions::None};
    Directions m_riverDirection2{Directions::None};
  };
}