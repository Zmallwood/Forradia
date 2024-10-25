namespace YrradiaSDL2.Game.CoreGameObjects
{
    public class Player
    {
        public System.Drawing.Point m_position = new (50, 50);
        public int m_ticksLastMove = 0;
        public int m_ticksLastSpeedChange = 0;
        public float m_movementSpeed = 0.0f;
        public System.Drawing.Point m_movementDirection = new (0, 0);

        public void Accelerate()
        {
            m_movementSpeed = Math.Min(3.0f, m_movementSpeed + 0.15f);
        }

        public void Decelerate()
        {
            m_movementSpeed = Math.Max(0.0f, m_movementSpeed - 0.15f);
        }

        public void UpdateMovement()
        {
            var newX = m_position.X + m_movementDirection.X;
            var newY = m_position.Y + m_movementDirection.Y;

            if (_.world.GetCurrentWorldArea().GetTile(newX, newY).m_ground == "GroundWater".GetHashCode())
            {
                return;
            }

            if (_.world.GetCurrentWorldArea().GetTile(newX, newY).m_mob != null)
            {
                return;
            }

            m_position = new(newX, newY);
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
