namespace YrradiaSDL2.Game.CoreGameObjects
{
    public class Player
    {
        public System.Drawing.Point m_position = new(50, 50);
        public System.Drawing.Point m_destination = new(-1, -1);
        public int m_ticksLastMove = 0;
        public int m_ticksLastSpeedChange = 0;
        public float m_movementSpeed = 0.0f;
        public System.Drawing.Point m_movementDirection = new(0, 0);
        public float m_hp = 10.0f;
        public float m_maxHP = 10.0f;
        public float m_sp = 10.0f;
        public float m_maxSP = 10.0f;
        public float m_mp = 10.0f;
        public float m_maxMP = 10.0f;
        public string m_name = "Unnamed";
        public int m_actionDurationTotal = 0;
        public int m_actionDurationRemaining = 0;
        private Action? m_currentAction = null;
        private int m_ticksLastActionUpdate = 0;

        public void SetAction(Action action, int actionDuration)
        {
            m_currentAction = action;
            m_actionDurationTotal = actionDuration;
            m_actionDurationRemaining = actionDuration;
        }

        public void UpdateActions()
        {
            if (Environment.TickCount > m_ticksLastActionUpdate + 500)
            {
                m_actionDurationRemaining--;
                if (m_actionDurationRemaining == 0)
                {
                    m_currentAction();
                    m_currentAction = null;
                    m_actionDurationTotal = 0;
                }
                m_ticksLastActionUpdate = Environment.TickCount;
            }
        }

        public void Accelerate()
        {
            m_movementSpeed = Math.Min(5.0f, m_movementSpeed + 0.15f);
        }

        public void Decelerate()
        {
            m_movementSpeed = Math.Max(0.0f, m_movementSpeed - 0.3f);
        }

        public void Update()
        {
            UpdateMovement();
        }

        private void UpdateMovement()
        {
            if (Environment.TickCount > _.player.m_ticksLastMove + 1000 / _.player.m_movementSpeed)
            {
                var newX = m_position.X + m_movementDirection.X;
                var newY = m_position.Y + m_movementDirection.Y;

                var tile = _.world.GetCurrentWorldArea().GetTile(newX, newY);

                if (tile.m_ground == "GroundWater".GetHashCode())
                {
                    return;
                }

                if (tile.m_mob != null)
                {
                    if (!_.mobIndex.MobIsFlying(tile.m_mob.m_type))
                    {
                        return;
                    }
                }

                foreach (var tangibleObject in tile.m_objects.m_objects)
                {
                    if (_.objectIndex.ObjectBlocksMovement(tangibleObject.m_type))
                    {
                        return;
                    }
                }

                m_position = new(newX, newY);
                _.player.m_ticksLastMove = Environment.TickCount;
            }
        }

        public void MoveNorth()
        {
            m_movementDirection.Y = -1;
        }

        public void MoveEast()
        {
            m_movementDirection.X = 1;
        }

        public void MoveSouth()
        {
            m_movementDirection.Y = 1;
        }

        public void MoveWest()
        {
            m_movementDirection.X = -1;
        }

        public void StopMove()
        {
            m_movementDirection = new(0, 0);
        }

        public void ResetMovementSpeed()
        {
            m_movementSpeed = 0.0f;
        }
    }
}
