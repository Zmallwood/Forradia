

namespace YrradiaSDL2.Game.Configuration
{
    public class MobProperty
    {
        public string name = "";
        public int level = 0;
        public int flags = 0;

        public MobProperty(string name, int level, int flags)
        {
            this.name = name;
            this.level = level;
            this.flags = flags;
        }
    }
}
