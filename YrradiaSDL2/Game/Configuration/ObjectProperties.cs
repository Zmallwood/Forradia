namespace YrradiaSDL2.Game.Configuration
{
    public class ObjectProperties
    {
        public Dictionary<int, ObjectProperty> m_properties = new();

        public ObjectProperties()
        {
            m_properties.Add("ObjectTree1".GetHashCode(), new("Tree", (int)ObjectFlags.BlocksMovement));
            m_properties.Add("ObjectTree2".GetHashCode(), new("Tree", (int)ObjectFlags.BlocksMovement));
            m_properties.Add("ObjectBush1".GetHashCode(), new("Bush", (int)ObjectFlags.BlocksMovement));
            m_properties.Add("ObjectStoneBoulder".GetHashCode(), new("Stone boulder", (int)ObjectFlags.BlocksMovement));
            m_properties.Add("ObjectTrain".GetHashCode(), new("Train", (int)ObjectFlags.BlocksMovement));
            m_properties.Add("ObjectTrainWagon".GetHashCode(), new("Train wagon", (int)ObjectFlags.BlocksMovement));
        }

        public bool ObjectBlocksMovement(int objectNameHash)
        {
            if (m_properties.ContainsKey(objectNameHash))
            {
                if ((m_properties[objectNameHash].flags & (int)ObjectFlags.BlocksMovement) != 0)
                {
                    return true;
                }
            }
            
            return false;
        }
    }
}
