namespace YrradiaSDL2.Game.WorldStructure
{
    public class WorldArea
    {
        private List<List<Tile>> m_tiles = new List<List<Tile>>();
        public Dictionary<Mob, System.Drawing.Point> m_mobsMirror = new();

        public WorldArea()
        {
            for (var x = 0; x < 100; x++)
            {
                m_tiles.Add(new List<Tile>());
                for (var y = 0; y < 100; y++)
                {
                    m_tiles[x].Add(new Tile());
                }
            }
        }

        public Tile GetTile(int x, int y)
        {
            return m_tiles[x][y];
        }

        public Tile GetTile(System.Drawing.Point coordinate)
        {
            return GetTile(coordinate.X, coordinate.Y);
        }
    }
}
