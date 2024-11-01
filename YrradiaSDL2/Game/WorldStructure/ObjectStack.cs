namespace YrradiaSDL2.Game.WorldStructure
{
    public class ObjectStack
    {
        public List<TangibleObject> m_objects = new();

        public void Add(string objectName)
        {
            m_objects.Add(new(objectName.GetHashCode()));
        }

        public void Add(TangibleObject tangibleObject)
        {
            m_objects.Add(tangibleObject);
        }

        public int Count()
        {
            return m_objects.Count;
        }

        public List<TangibleObject> All()
        {
            return m_objects;
        }

        public TangibleObject? Pop()
        {
            if (m_objects.Count > 0)
            {
                var result = m_objects.Last();
                m_objects.Remove(result);
                return result;
            }
            return null;
        }

        public bool Contains(string objectName)
        {
            foreach (var tangibleObject in m_objects)
            {
                if (tangibleObject.m_type == objectName.GetHashCode())
                {
                    return true;
                }
            }

            return false;
        }

        public void Remove(TangibleObject tangibleObject)
        {
            m_objects.Remove(tangibleObject);
        }

        public void Clear()
        {
            m_objects.Clear();
        }
    }
}
