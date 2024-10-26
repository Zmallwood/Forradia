namespace YrradiaSDL2.ForradiaTheme.Scenes.MainScene.MainSceneGUI
{
    public class GUIWindowInventory : GUIWindow
    {
        protected override PointF GetInitialPosition()
        {
            return new(0.5f, 0.2f);
        }

        protected override string GetTitle()
        {
            return "Inventory";
        }

        protected override Size GetSize()
        {
            return new(200, 400);
        }
    }
}
