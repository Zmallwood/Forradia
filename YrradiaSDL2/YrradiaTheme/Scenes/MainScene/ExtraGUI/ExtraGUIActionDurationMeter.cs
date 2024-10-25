
namespace YrradiaSDL2.YrradiaTheme.Scenes.MainScene.ExtraGUI
{
    public class ExtraGUIActionDurationMeter
    {
        public void Render()
        {
            if (_.player.m_actionDurationTotal == 0)
            {
                return;
            }

            var x = 0.4f;
            var y = 0.3f;
            var height = 0.03f;
            var widthFull = 0.2f;
            var widthCurrent = widthFull * (float)_.player.m_actionDurationRemaining / _.player.m_actionDurationTotal;

            _.imageRenderer.DrawImage("Black", x, y, widthFull, height);
            _.imageRenderer.DrawImage("Yellow", x, y, widthCurrent, height);
            _.imageRenderer.DrawImage("BlackMeterBorders", x, y, widthFull, height);
        }
    }
}
