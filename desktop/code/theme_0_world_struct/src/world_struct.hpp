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
        none,
        n,
        e,
        s,
        w,
        ne,
        se,
        sw,
        nw
    };

    class Creature
    {
      public:
        Creature(StringView type_name) : type_{Hash(type_name)}
        {
            Initialize();
        }

        auto GetType() const
        {
            return type_;
        }

        auto GetTicksLastMovement() const
        {
            return ticks_last_movement_;
        }

        void SetTicksLastMovement(int value)
        {
            ticks_last_movement_ = value;
        }

        auto GetMovementSpeed() const
        {
            return movement_speed_;
        }

        auto GetDestination() const
        {
            return destination_;
        }

        void SetDestination(Point value)
        {
            destination_ = value;
        }

      private:
        void Initialize();

        int type_{0};
        int ticks_last_movement_{0};
        float movement_speed_{2.0f};
        Point destination_{-1, -1};
    };

    class NPC
    {
      public:
        NPC(StringView type_name) : type_{Hash(type_name)}
        {
            Initialize();
        }

        auto GetType() const
        {
            return type_;
        }

        auto GetName() const
        {
            return name_;
        }

        auto GetTicksLastMovement() const
        {
            return ticks_last_movement_;
        }

        void SetTicksLastMovement(int value)
        {
            ticks_last_movement_ = value;
        }

        auto GetMovementSpeed() const
        {
            return movement_speed_;
        }

        auto GetDestination() const
        {
            return destination_;
        }

        void SetDestination(Point value)
        {
            destination_ = value;
        }

        auto GetTicksNextSpontaneousSpeech() const
        {
            return ticks_next_spontaneous_speech_;
        }

        void SetTicksNextSpontaneousSpeech(int value)
        {
            ticks_next_spontaneous_speech_ = value;
        }

      private:
        void Initialize();

        void GenerateName();

        int type_{0};
        String name_;
        int ticks_last_movement_{0};
        float movement_speed_{2.0f};
        Point destination_{-1, -1};
        int ticks_next_spontaneous_speech_{0};
    };

    class Object
    {
      public:
        Object(StringView object_type_name) : type_(Hash(object_type_name))
        {
        }

        auto GetType() const
        {
            return type_;
        }

      private:
        int type_{0};
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
            return trunk_parts_;
        }

        auto GetNeedleTypes() const
        {
            return needle_types_;
        }

        auto GetWidthFactor() const
        {
            return width_factor_;
        }

      private:
        void Initialize(StringView obj_type_name);

        Vector<PointF> trunk_parts_;
        Vector<int> needle_types_;
        float width_factor_{1.0f};
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
            return objects_;
        }

      private:
        Vector<SharedPtr<Object>> objects_;
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
            return ground_;
        }

        void SetGround(StringView ground_name);

        auto GetObjectsStack() const
        {
            return objects_stack_;
        }

        auto GetCreature() const
        {
            return creature_;
        }

        void SetCreature(SharedPtr<Forradia::Theme0::WorldStructure::Creature> val)
        {
            creature_ = val;
        }

        auto GetNPC() const
        {
            return npc_;
        }

        void SetNPC(SharedPtr<Forradia::Theme0::WorldStructure::NPC> value)
        {
            npc_ = value;
        }

        auto GetElevation() const
        {
            return elevation_;
        }

        void SetElevation(int value)
        {
            elevation_ = value;
        }

        auto GetWaterDepth() const
        {
            return water_depth_;
        }

        void SetWaterDepth(int value)
        {
            water_depth_ = value;
        }

        auto GetRiverDirection1() const
        {
            return river_direction_1_;
        }

        void SetRiverDirection1(Directions value)
        {
            river_direction_1_ = value;
        }

        auto GetRiverDirection2() const
        {
            return river_direction_2_;
        }

        void SetRiverDirection2(Directions value)
        {
            river_direction_2_ = value;
        }

      private:
        void Initialize();

        int ground_{0};
        SharedPtr<Forradia::Theme0::WorldStructure::ObjectsStack> objects_stack_;
        SharedPtr<Forradia::Theme0::WorldStructure::Creature> creature_;
        SharedPtr<Forradia::Theme0::WorldStructure::NPC> npc_;
        int elevation_{0};
        int water_depth_{0};
        Directions river_direction_1_{Directions::none};
        Directions river_direction_2_{Directions::none};
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
            return creatures_mirror_;
        }

        auto &GetNPCsMirrorRef()
        {
            return npcs_mirror_;
        }

      private:
        void Initialize(Size w_area_sz, float world_scaling);

        Vector<Vector<SharedPtr<Tile>>> tiles_;
        std::map<SharedPtr<Creature>, Point> creatures_mirror_;
        std::map<SharedPtr<NPC>, Point> npcs_mirror_;
    };

    class World
    {
      public:
        void Initialize(Size w_area_sz, float world_scaling);

        auto GetCurrentWorldArea() const
        {
            return current_world_area_;
        }

      private:
        SharedPtr<WorldArea> current_world_area_;
    };
}
using namespace WorldStructure;
#define _HIDE_FROM_OUTLINER_WORLD_STRUCT_BOTTOM_ }
_HIDE_FROM_OUTLINER_WORLD_STRUCT_BOTTOM_
_NS_END_