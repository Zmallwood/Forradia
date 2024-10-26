

namespace YrradiaSDL2.ForradiaTheme.Scenes.MainScene.ExtraGUI.ExtraGUIActionMenu.Actions
{
    public class PlayerActionCreateCampfire : PlayerAction
    {
        public override string GetLabel()
        {
            return "Create campfire";
        }

        public override void Perform(System.Drawing.Point coordinate)
        {
            if (coordinate.X >= 0 && coordinate.Y >= 0)
            {
                var tile = _.world.GetCurrentWorldArea().GetTile(coordinate.X, coordinate.Y);

                if (tile != null)
                {
                    foreach (var tangibleObject in tile.m_objects.m_objects)
                    {
                        if (tangibleObject.m_type == "ObjectWoodLog".GetHashCode())
                        {
                            var absDx = Math.Abs(coordinate.X - _.player.m_position.X);
                            var absDy = Math.Abs(coordinate.Y - _.player.m_position.Y);
                            if (absDx > 1 || absDy > 1)
                            {
                                _.textOut.Print("You are too far away to craft.");
                                return;
                            }
                            _.player.SetAction(() => {
                                tile.m_objects.Remove(tangibleObject);
                                tile.m_objects.Add("ObjectCampfire");
                                _.textOut.Print("You create a campfire.");
                            }, 10);
                            return;
                        }
                    }
                }
            }
        }
    }
}
