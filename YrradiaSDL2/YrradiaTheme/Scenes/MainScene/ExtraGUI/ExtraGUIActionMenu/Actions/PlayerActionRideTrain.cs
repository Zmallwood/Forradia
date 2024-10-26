

namespace YrradiaSDL2.YrradiaTheme.Scenes.MainScene.ExtraGUI.ExtraGUIActionMenu.Actions
{
    public class PlayerActionRideTrain : PlayerAction
    {
        public override string GetLabel()
        {
            return "Ride train";
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
                        if (tangibleObject.m_type == "ObjectTrain".GetHashCode() ||
                            tangibleObject.m_type == "ObjectTrainWagon".GetHashCode())
                        {
                            var absDx = Math.Abs(coordinate.X - _.player.m_position.X);
                            var absDy = Math.Abs(coordinate.Y - _.player.m_position.Y);
                            if (absDx > 1 || absDy > 1)
                            {
                                _.textOut.Print("You are too far away to ride the train.");
                                return;
                            }
                            _.player.SetAction(() => {
                                _.worldGenerator.GenerateWorld();
                                _.textOut.Print("You travel with the train to a new area.");
                            }, 10);
                            return;
                        }
                    }
                }
            }
        }
    }
}
