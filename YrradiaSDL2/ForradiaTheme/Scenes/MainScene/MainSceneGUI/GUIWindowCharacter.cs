
namespace YrradiaSDL2.ForradiaTheme.Scenes.MainScene.MainSceneGUI
{
    public class GUIWindowCharacter : GUIWindow
    {
        protected override PointF GetInitialPosition()
        {
            return new(0.2f, 0.2f);
        }

        protected override string GetTitle()
        {
            return "Character";
        }

        protected override Size GetSize()
        {
            return new(200, 400);
        }
    }
}
