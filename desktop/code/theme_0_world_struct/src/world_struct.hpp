/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

_NS_START_
#define _HIDE_FROM_OUTLINER_WORLD_STRUCT_TOP_                                  \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_WORLD_STRUCT_TOP_
namespace WorldStructure
{
    enum class Directions
    {
        None,
        N,
        E,
        S,
        W,
        NE,
        SE,
        SW,
        NW
    };

    class Creature
    {
      public:
        Creature(StringView type_name) : m_type{Hash(type_name)}
        {
            Initialize();
        }

        auto GetType() const
        {
            return m_type;
        }

        auto GetTicksLastMovement() const
        {
            return m_ticksLastMovement;
        }

        void SetTicksLastMovement(int value)
        {
            m_ticksLastMovement = value;
        }

        auto GetMovementSpeed() const
        {
            return m_movementSpeed;
        }

        auto GetDestination() const
        {
            return m_destination;
        }

        void SetDestination(Point value)
        {
            m_destination = value;
        }

      private:
        void Initialize();

        int m_type{0};
        int m_ticksLastMovement{0};
        float m_movementSpeed{2.0f};
        Point m_destination{-1, -1};
    };

    class NPC
    {
      public:
        NPC(StringView type_name) : m_type{Hash(type_name)}
        {
            Initialize();
        }

        auto GetType() const
        {
            return m_type;
        }

        auto GetName() const
        {
            return m_name;
        }

        auto GetTicksLastMovement() const
        {
            return m_ticksLastMovement;
        }

        void SetTicksLastMovement(int value)
        {
            m_ticksLastMovement = value;
        }

        auto GetMovementSpeed() const
        {
            return m_movementSpeed;
        }

        auto GetDestination() const
        {
            return m_destination;
        }

        void SetDestination(Point value)
        {
            m_destination = value;
        }

        auto GetTicksNextSpontaneousSpeech() const
        {
            return m_ticksNextSpontaneousSpeech;
        }

        void SetTicksNextSpontaneousSpeech(int value)
        {
            m_ticksNextSpontaneousSpeech = value;
        }

      private:
        void Initialize();

        void GenerateName();

        int m_type{0};
        String m_name;
        int m_ticksLastMovement{0};
        float m_movementSpeed{2.0f};
        Point m_destination{-1, -1};
        int m_ticksNextSpontaneousSpeech{0};
    };

    class Object
    {
      public:
        Object(StringView object_type_name) : m_type(Hash(object_type_name))
        {
        }

        auto GetType() const
        {
            return m_type;
        }

      private:
        int m_type{0};
    };

    class TreeObject : public Object
    {
      public:
        TreeObject(StringView obj_type_name) : Object(obj_type_name)
        {
            Initialize(obj_type_name);
        }

        auto GetTrunkParts() const
        {
            return m_trunkParts;
        }

        auto GetNeedleTypes() const
        {
            return m_needleTypes;
        }

        auto GetWidthFactor() const
        {
            return m_widthFactor;
        }

      private:
        void Initialize(StringView obj_type_name);

        Vector<PointF> m_trunkParts;
        Vector<int> m_needleTypes;
        float m_widthFactor{1.0f};
    };

    class ObjectsStack
    {
      public:
        void ClearObjects();

        void AddObject(StringView obj_type_name);

        void AddTreeObject(StringView obj_type_name);

        int GetSize() const;

        auto GetObjects() const
        {
            return m_objects;
        }

      private:
        Vector<SharedPtr<Object>> m_objects;
    };

    class Tile
    {
      public:
        Tile()
        {
            Initialize();
        }

        auto GetGround() const
        {
            return m_ground;
        }

        void SetGround(StringView ground_name);

        auto GetObjectsStack() const
        {
            return m_objectsStack;
        }

        auto GetCreature() const
        {
            return m_creature;
        }

        void
        SetCreature(SharedPtr<Forradia::Theme0::WorldStructure::Creature> val)
        {
            m_creature = val;
        }

        auto GetNPC() const
        {
            return m_npc;
        }

        void SetNPC(SharedPtr<Forradia::Theme0::WorldStructure::NPC> value)
        {
            m_npc = value;
        }

        auto GetElevation() const
        {
            return m_elevation;
        }

        void SetElevation(int value)
        {
            m_elevation = value;
        }

        auto GetWaterDepth() const
        {
            return m_waterDepth;
        }

        void SetWaterDepth(int value)
        {
            m_waterDepth = value;
        }

        auto GetRiverDirection1() const
        {
            return m_riverDirection1;
        }

        void SetRiverDirection1(Directions value)
        {
            m_riverDirection1 = value;
        }

        auto GetRiverDirection2() const
        {
            return m_riverDirection2;
        }

        void SetRiverDirection2(Directions value)
        {
            m_riverDirection2 = value;
        }

      private:
        void Initialize();

        int m_ground{0};
        SharedPtr<Forradia::Theme0::WorldStructure::ObjectsStack>
            m_objectsStack;
        SharedPtr<Forradia::Theme0::WorldStructure::Creature> m_creature;
        SharedPtr<Forradia::Theme0::WorldStructure::NPC> m_npc;
        int m_elevation{0};
        int m_waterDepth{0};
        Directions m_riverDirection1{Directions::None};
        Directions m_riverDirection2{Directions::None};
    };

    class WorldArea
    {
      public:
        WorldArea(Size w_area_sz, float world_scaling)
        {
            Initialize(w_area_sz, world_scaling);
        }

        Size GetSize() const;

        bool IsValidCoordinate(int x, int y) const;

        bool IsValidCoordinate(Point coord) const;

        SharedPtr<Tile> GetTile(int x, int y) const;

        SharedPtr<Tile> GetTile(Point coord) const;

        auto &GetCreaturesMirrorRef()
        {
            return m_creaturesMirror;
        }

        auto &GetNPCsMirrorRef()
        {
            return m_npcsMirror;
        }

      private:
        void Initialize(Size w_area_sz, float world_scaling);

        Vector<Vector<SharedPtr<Tile>>> m_tiles;
        std::map<SharedPtr<Creature>, Point> m_creaturesMirror;
        std::map<SharedPtr<NPC>, Point> m_npcsMirror;
    };

    class World
    {
      public:
        void Initialize(Size w_area_sz, float world_scaling);

        auto GetCurrentWorldArea() const
        {
            return m_currentWorldArea;
        }

      private:
        SharedPtr<WorldArea> m_currentWorldArea;
    };
}
using namespace WorldStructure;
#define _HIDE_FROM_OUTLINER_WORLD_STRUCT_BOTTOM_ }
_HIDE_FROM_OUTLINER_WORLD_STRUCT_BOTTOM_
_NS_END_