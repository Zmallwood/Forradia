namespace YrradiaSDL2.Game.WorldStructure
{
    public class World
    {
        private WorldArea m_currentWorldArea = new WorldArea();

        public WorldArea GetCurrentWorldArea() { return m_currentWorldArea; }
    }
}
