/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia::Theme0 {
  class Object;

  /**
   * Represents the inventory of objects for the player.
   * TODO: Decide if should be used also for other entities.
   */
  class PlayerObjectsInventory {
   public:
    /**
     * Constructor.
     */
    PlayerObjectsInventory();

    /**
     * Gets an object from the inventory.
     *
     * @param index The index of the object.
     * @return The object.
     */
    auto GetObject(int index) -> std::shared_ptr<Object>;

    auto GetObjectPtrPtr(int index) -> std::shared_ptr<Object> *;

    /**
     * Adds an object to the inventory.
     *
     * @param objectType The type of the object as a hash.
     */
    auto AddObject(int objectType) -> void;

    /**
     * Adds an object to the inventory.
     *
     * @param objectName The name of the object as a string.
     */
    auto AddObject(std::string_view objectName) -> void;

    /**
     * Counts the number of objects in the inventory that have the given name.
     *
     * @param objectName The name of the object as a string.
     * @return The number of objects in the inventory that have the given name.
     */
    auto CountHasObject(std::string_view objectName) -> int;

    /**
     * Removes objects from the inventory with the specified name and count.
     *
     * @param objectName The name of the object as a string.
     * @param count How many objects of the given type to remove.
     */
    auto RemoveObject(std::string_view objectName, int count = 1) -> void;

   private:
    std::vector<std::shared_ptr<Object>> m_objects;
  };
}
