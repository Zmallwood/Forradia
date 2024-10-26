namespace YrradiaSDL2.ForradiaTheme.Scenes.MainScene
{
    public class MainScene : Scene
    {
        public bool m_paused = false;

        public override void Initialize()
        {
            m_gui.AddComponent(new GUIButton("", new(0.82f, 0.9f), () => { }, false, new (0.05f, _.canvasUtilities.ConvertWidthToHeight(0.05f)), "GUIButtonRoundCharacter", "GUIButtonRoundCharacterHovered"));
            m_gui.AddComponent(new GUIButton("", new(0.88f, 0.9f), () => { }, false, new (0.05f, _.canvasUtilities.ConvertWidthToHeight(0.05f)), "GUIButtonRoundInventory", "GUIButtonRoundInventoryHovered"));
            m_gui.AddComponent(new GUIButton("", new(0.94f, 0.9f), () => { _.extraGUISystemMenu.ToggleVisibility(); }, false, new (0.05f, _.canvasUtilities.ConvertWidthToHeight(0.05f)), "GUIButtonRoundSystem", "GUIButtonRoundSystemHovered"));
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
