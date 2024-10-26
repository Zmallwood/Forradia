namespace YrradiaSDL2.YrradiaTheme.Scenes.MainScene
{
    public class MainScene : Scene
    {
        public bool m_paused = false;

        public override void Initialize()
        {
            m_gui.AddComponent(new GUIButton("", new(0.6f, 0.92f), () => { }, false, new (0.05f, _.canvasUtilities.ConvertWidthToHeight(0.05f)), "GUIButtonRoundCharacter", "GUIButtonRoundCharacterHovered"));
        }

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
