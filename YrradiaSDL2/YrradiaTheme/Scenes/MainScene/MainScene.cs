namespace YrradiaSDL2.YrradiaTheme.Scenes.MainScene
{
    public class MainScene : Scene
    {
        public bool m_paused = false;

        public override void OnEnter()
        {
            base.OnEnter();

            _.playerPositioner.EnsureGoodPlayerPosition();
            _.textOut.Print("Entering the world.");
        }

        protected override void UpdateDerived()
        {
            if (!m_paused)
            {
                _.keyboardMovement.Update();
                _.tileHovering.Update();
                _.mobMovement.Update();
                _.extraGUIActionMenu.Update();
                _.player.UpdateActions();
            }
            _.extraGUISystemMenu.Update();
        }

        protected override void RenderDerived()
        {
            _.worldView.Render();
            _.extraGUITextConsole.Render();
            _.extraGUIStatusPanel.Render();
            _.extraGUIActionMenu.Render();
            _.extraGUIActionDurationMeter.Render();
            _.extraGUISystemMenu.Render();
        }
    }
}
