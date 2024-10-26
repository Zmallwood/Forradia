namespace YrradiaSDL2.Game.Configuration
{
    public class MobIndex
    {
        public Dictionary<int, MobProperty> m_properties = new();

        public MobIndex()
        {
            m_properties.Add("MobRedBird".GetHashCode(), new("Red bird", 0, (int)MobFlags.Unlabeled | (int)MobFlags.Unattackable | (int)MobFlags.Flying));
            m_properties.Add("MobRat".GetHashCode(), new("Rat", 1, 0));
            m_properties.Add("MobSnake".GetHashCode(), new("Snake", 2, 0));
            m_properties.Add("MobBear".GetHashCode(), new("Bear", 5, 0));
        }

        public string GetMobName(int mobNameHash)
        {
            return m_properties[mobNameHash].name;
        }

        public int GetMobLevel(int mobNameHash)
        {
            return m_properties[mobNameHash].level;
        }

        public bool MobIsUnlabeled(int objectNameHash)
        {
            if (m_properties.ContainsKey(objectNameHash))
            {
                if ((m_properties[objectNameHash].flags & (int)MobFlags.Unlabeled) != 0)
                {
                    return true;
                }
            }

            return false;
        }

        public bool MobIsUnattackable(int objectNameHash)
        {
            if (m_properties.ContainsKey(objectNameHash))
            {
                if ((m_properties[objectNameHash].flags & (int)MobFlags.Unattackable) != 0)
                {
                    return true;
                }
            }

            return false;
        }

        public bool MobIsFlying(int objectNameHash)
        {
            if (m_properties.ContainsKey(objectNameHash))
            {
                if ((m_properties[objectNameHash].flags & (int)MobFlags.Flying) != 0)
                {
                    return true;
                }
            }

            return false;
        }
    }
}
