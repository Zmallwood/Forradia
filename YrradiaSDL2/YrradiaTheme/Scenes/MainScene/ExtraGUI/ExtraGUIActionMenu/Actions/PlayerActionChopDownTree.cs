

namespace YrradiaSDL2.YrradiaTheme.Scenes.MainScene.ExtraGUI.ExtraGUIActionMenu.Actions
{
    public class PlayerActionChopDownTree : PlayerAction
    {
        public override string GetLabel()
        {
            return "Chop down tree";
        }

        public override void Perform(System.Drawing.Point coordinate)
        {
            if (coordinate.X >= 0 && coordinate.Y >= 0)
            {
                var tile = _.world.GetCurrentWorldArea().GetTile(coordinate.X, coordinate.Y);

                if (tile != null) {
                    foreach (var tangibleObject in tile.m_objects.m_objects)
                    {
                        if (tangibleObject.m_type == "ObjectTree1".GetHashCode() ||
                            tangibleObject.m_type == "ObjectTree2".GetHashCode())
                        {
                            _.player.SetAction(() => { tile.m_objects.Remove(tangibleObject); }, 10);
                            return;
                        }
                    }
                }
            }
        }
    }
}
