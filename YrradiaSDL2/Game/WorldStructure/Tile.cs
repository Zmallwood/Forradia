namespace YrradiaSDL2.Game.WorldStructure
{
    public class Tile
    {
        public int m_ground = 0;
        public int m_layer = 0;
        public ObjectStack m_objects = new();
        public Mob? m_mob = null;
        public int m_elevation = 0;
    }
}
