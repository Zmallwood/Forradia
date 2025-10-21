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
        Creature(StringView type_name) : type_{hash(type_name)}
        {
            init();
        }

        auto type() const
        {
            return type_;
        }

        auto ticks_last_move() const
        {
            return ticks_last_move_;
        }

        void set_ticks_last_move(int value)
        {
            ticks_last_move_ = value;
        }

        auto movem_spd() const
        {
            return movem_spd_;
        }

        auto dest() const
        {
            return dest_;
        }

        void set_dest(Point val)
        {
            dest_ = val;
        }

      private:
        void init();

        int type_{0};
        int ticks_last_move_{0};
        float movem_spd_{2.0f};
        Point dest_{-1, -1};
    };

    class NPC
    {
      public:
        NPC(StringView type_name) : type_{hash(type_name)}
        {
            init();
        }

        auto type() const
        {
            return type_;
        }

        auto name() const
        {
            return name_;
        }

        auto ticks_last_move() const
        {
            return ticks_last_move_;
        }

        void set_ticks_last_move(int value)
        {
            ticks_last_move_ = value;
        }

        auto movem_spd() const
        {
            return movem_spd_;
        }

        auto dest() const
        {
            return dest_;
        }

        void set_dest(Point val)
        {
            dest_ = val;
        }

        auto ticks_next_spontaneous_speech() const
        {
            return ticks_next_spontaneous_speech_;
        }

        void set_ticks_next_spontaneous_speech(int value)
        {
            ticks_next_spontaneous_speech_ = value;
        }

      private:
        void init();

        void gen_name();

        int type_{0};
        String name_;
        int ticks_last_move_{0};
        float movem_spd_{2.0f};
        Point dest_{-1, -1};
        int ticks_next_spontaneous_speech_{0};
    };

    class Object
    {
      public:
        Object(StringView object_type_name) : type_(hash(object_type_name))
        {
        }

        auto type() const
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
            init(obj_type_name);
        }

        auto trunk_parts() const
        {
            return trunk_parts_;
        }

        auto needle_types() const
        {
            return needle_types_;
        }

        auto w_factor() const
        {
            return w_factor_;
        }

      private:
        void init(StringView obj_type_name);

        Vector<PointF> trunk_parts_;
        Vector<int> needle_types_;
        float w_factor_{1.0f};
    };

    class ObjectsStack
    {
      public:
        void clear_objs();

        void add_obj(StringView obj_type_name);

        void add_tree_obj(StringView obj_type_name);

        int get_sz() const;

        auto objects() const
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
            init();
        }

        auto ground() const
        {
            return ground_;
        }

        void set_ground(StringView ground_name);

        auto objects_stack() const
        {
            return objects_stack_;
        }

        auto creature() const
        {
            return creature_;
        }

        void set_creature(SharedPtr<Forradia::Theme0::WorldStructure::Creature> val)
        {
            creature_ = val;
        }

        auto npc() const
        {
            return npc_;
        }

        void set_npc(SharedPtr<Forradia::Theme0::WorldStructure::NPC> val)
        {
            npc_ = val;
        }

        auto elev() const
        {
            return elev_;
        }

        void set_elev(int val)
        {
            elev_ = val;
        }

        auto water_depth() const
        {
            return water_depth_;
        }

        void set_water_depth(int val)
        {
            water_depth_ = val;
        }

        auto river_dir_1() const
        {
            return river_dir_1_;
        }

        void set_river_dir_1(Directions val)
        {
            river_dir_1_ = val;
        }

        auto river_dir_2() const
        {
            return river_dir_2_;
        }

        void set_river_dir_2(Directions val)
        {
            river_dir_2_ = val;
        }

      private:
        void init();

        int ground_{0};
        SharedPtr<Forradia::Theme0::WorldStructure::ObjectsStack> objects_stack_;
        SharedPtr<Forradia::Theme0::WorldStructure::Creature> creature_;
        SharedPtr<Forradia::Theme0::WorldStructure::NPC> npc_;
        int elev_{0};
        int water_depth_{0};
        Directions river_dir_1_{Directions::none};
        Directions river_dir_2_{Directions::none};
    };

    class WorldArea
    {
      public:
        WorldArea(Size w_area_sz, float world_scaling)
        {
            init(w_area_sz, world_scaling);
        }

        Size get_sz() const;

        bool is_valid_coord(int x, int y) const;

        bool is_valid_coord(Point coord) const;

        SharedPtr<Tile> get_tl(int x, int y) const;

        SharedPtr<Tile> get_tl(Point coord) const;

        auto &creatures_mirror_ref()
        {
            return creatures_mirror_;
        }

        auto &npcs_mirror_ref()
        {
            return npcs_mirror_;
        }

      private:
        void init(Size w_area_sz, float world_scaling);

        Vector<Vector<SharedPtr<Tile>>> tiles_;
        std::map<SharedPtr<Creature>, Point> creatures_mirror_;
        std::map<SharedPtr<NPC>, Point> npcs_mirror_;
    };

    class world
    {
      public:
        void init(Size w_area_sz, float world_scaling);

        auto curr_w_area() const
        {
            return curr_w_area_;
        }

      private:
        SharedPtr<WorldArea> curr_w_area_;
    };
}
using namespace WorldStructure;
#define _HIDE_FROM_OUTLINER_WORLD_STRUCT_BOTTOM_ }
_HIDE_FROM_OUTLINER_WORLD_STRUCT_BOTTOM_
_NS_END_