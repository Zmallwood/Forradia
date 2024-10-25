namespace YrradiaSDL2.YrradiaTheme.Scenes.MainScene
{
    public class MainScene : Scene
    {
        public override void OnEnter()
        {
            base.OnEnter();

            _.playerPositioner.EnsureGoodPlayerPosition();
        }

        protected override void UpdateDerived()
        {
            _.keyboardMovement.Update();
            _.tileHovering.Update();
            _.mobMovement.Update();
            _.extraGUIActionMenu.Update();
            _.player.UpdateActions();
        }

        protected override void RenderDerived()
        {
            _.worldView.Render();
            _.extraGUIStatusPanel.Render();
            _.extraGUIActionMenu.Render();
            _.extraGUIActionDurationMeter.Render();
        }
    }
}
