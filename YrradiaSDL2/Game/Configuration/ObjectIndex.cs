namespace YrradiaSDL2.Game.Configuration
{
    public class ObjectIndex
    {
        public Dictionary<int, ObjectProperty> m_properties = new();

        public ObjectIndex()
        {
            m_properties.Add("ObjectTree1".GetHashCode(), new("Tree", (int)ObjectFlags.BlocksMovement | (int)ObjectFlags.Unmovable));
            m_properties.Add("ObjectTree2".GetHashCode(), new("Tree", (int)ObjectFlags.BlocksMovement | (int)ObjectFlags.Unmovable));
            m_properties.Add("ObjectBush1".GetHashCode(), new("Bush", (int)ObjectFlags.BlocksMovement | (int)ObjectFlags.Unmovable));
            m_properties.Add("ObjectStoneBoulder".GetHashCode(), new("Stone boulder", (int)ObjectFlags.BlocksMovement | (int)ObjectFlags.Unmovable));
            m_properties.Add("ObjectTrain".GetHashCode(), new("Train", (int)ObjectFlags.BlocksMovement | (int)ObjectFlags.Unmovable));
            m_properties.Add("ObjectTrainWagon".GetHashCode(), new("Train wagon", (int)ObjectFlags.BlocksMovement | (int)ObjectFlags.Unmovable));
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
