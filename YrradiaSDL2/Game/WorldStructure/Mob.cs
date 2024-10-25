namespace YrradiaSDL2.Game.WorldStructure
{
    public class Mob
    {
        public int m_type = 0;
        public int m_ticksLastMove = 0;
        public float m_movementSpeed = 0.0f;
        public System.Drawing.Point m_destination = new(-1, -1);
        public System.Drawing.Point m_movementDirection = new(0, 0);
        public int m_ticksLastSpeedChange = 0;
        public System.Drawing.Point m_moveStartCrd = new(-1, -1);

        public Mob(string type) : this(type.GetHashCode())
        {
        }

        public Mob(int typeHash)
        {
            m_type = typeHash;
            m_ticksLastMove = Environment.TickCount + Random.Shared.Next((int)(1000 / 3.0f));
        }

        public void Accelerate()
        {
            m_movementSpeed = Math.Min(1.0f, m_movementSpeed + 0.05f);
        }

        public void Decelerate()
        {
            m_movementSpeed = Math.Max(0.0f, m_movementSpeed - 0.05f);
        }

        public void ResetSpeed()
        {
            m_movementSpeed = 0.0f;
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
    }
}
