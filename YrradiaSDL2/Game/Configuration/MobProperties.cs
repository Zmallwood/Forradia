namespace YrradiaSDL2.Game.Configuration
{
    public class MobProperties
    {
        public Dictionary<int, MobProperty> m_properties = new();

        public MobProperties()
        {
            m_properties.Add("MobRat".GetHashCode(), new("Rat", 1));
            m_properties.Add("MobSnake".GetHashCode(), new("Snake", 2));
            m_properties.Add("MobBear".GetHashCode(), new("Bear", 5));
        }

        public string GetMobName(int mobNameHash)
        {
            return m_properties[mobNameHash].name;
        }

        public int GetMobLevel(int mobNameHash)
        {
            return m_properties[mobNameHash].level;
        }
    }
}
