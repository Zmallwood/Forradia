/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "WorldGeneratorEntities.hpp"
#include "Creature.hpp"
#include "ObjectsStack.hpp"
#include "Robot.hpp"
#include "Tile.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0 {
void WorldGeneratorEntities::GenerateEntities() const {
  GenerateCreaturesInEcosystems();
  GenerateRobotsInAreas();
}

void WorldGeneratorEntities::GenerateRobotsInAreas() const {
  auto worldArea{GetWorldArea()};
  auto worldAreaSize{worldArea->GetSize()};
  auto worldScaling{GetWorldScaling()};

  // Generate robots in clusters and patrol areas.
  // Robots avoid water but can be found in various terrain types.

  auto numRobotClusters{38 + GetRandomInt(7)};

  // Generate robots in clusters.
  for (auto cluster = 0; cluster < numRobotClusters; cluster++) {
    auto centerX{GetRandomInt(worldAreaSize.width)};
    auto centerY{GetRandomInt(worldAreaSize.height)};

    auto centerTile = worldArea->GetTile(centerX, centerY);

    if (!centerTile || centerTile->GetGround() == Hash("GroundWater")) {
      continue;
    }

    auto clusterRadius{10 + GetRandomInt(15)};
    auto robotsInCluster{5 + GetRandomInt(10)};

    // Generate robots in the cluster.
    for (auto r = 0; r < robotsInCluster; r++) {
      // Generate a random angle.
      auto angle = GetRandomInt(360) * M_PI / 180.0f;

      // Generate a random distance.
      auto distance = GetRandomInt(clusterRadius);

      auto robotX = centerX + CInt(std::cos(angle) * distance);
      auto robotY = centerY + CInt(std::sin(angle) * distance);

      if (!worldArea->IsValidCoordinate(robotX, robotY)) {
        continue;
      }

      auto robotTile = worldArea->GetTile(robotX, robotY);

      if (!robotTile || robotTile->GetRobot() || robotTile->GetGround() == Hash("GroundWater")) {
        continue;
      }

      auto newRobot{std::make_shared<Theme0::Robot>("RobotMechWolf", robotX, robotY)};

      robotTile->SetRobot(newRobot);

      worldArea->GetRobotsMirrorRef().insert({robotTile->GetRobot(), {robotX, robotY}});
    }
  }

  // Also add scattered robots throughout the world.
  auto numScatteredRobots{220 * worldScaling + GetRandomInt(40 * worldScaling)};

  for (auto i = 0; i < numScatteredRobots; i++) {
    auto x{GetRandomInt(worldAreaSize.width)};
    auto y{GetRandomInt(worldAreaSize.height)};

    auto tile{worldArea->GetTile(x, y)};

    if (!tile || tile->GetRobot() || tile->GetGround() == Hash("GroundWater")) {
      continue;
    }

    // Robots can appear anywhere except water, with equal probability.

    if (GetRandomInt(100) < 15) {
      auto newRobot{std::make_shared<Theme0::Robot>("RobotMechWolf", x, y)};

      tile->SetRobot(newRobot);

      worldArea->GetRobotsMirrorRef().insert({tile->GetRobot(), {x, y}});
    }
  }
}

bool WorldGeneratorEntities::IsNearWater(int x, int y, int radius) const {
  for (auto checkY = y - radius; checkY <= y + radius; checkY++) {
    for (auto checkX = x - radius; checkX <= x + radius; checkX++) {
      if (!GetWorldArea()->IsValidCoordinate(checkX, checkY)) {
        continue;
      }

      auto tile{GetWorldArea()->GetTile(checkX, checkY)};

      if (tile && tile->GetGround() == Hash("GroundWater")) {
        auto distance{GetDistance(x, y, checkX, checkY)};

        if (distance <= radius) {
          return true;
        }
      }
    }
  }

  return false;
}
}