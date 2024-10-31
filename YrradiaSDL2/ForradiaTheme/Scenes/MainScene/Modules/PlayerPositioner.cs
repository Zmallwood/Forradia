using YrradiaSDL2.Game.WorldStructure;

namespace YrradiaSDL2.ForradiaTheme.Scenes.MainScene.Modules
{
    public class PlayerPositioner
    {
        public void EnsureGoodPlayerPosition()
        {
            var worldArea = _.world.GetCurrentWorldArea();
            while (worldArea.GetTile(_.player.m_position).m_ground == "GroundWater".GetHashCode())
            {
                _.player.m_position = new System.Drawing.Point(Random.Shared.Next(100), Random.Shared.Next(100));
            }
        }
    }
}
