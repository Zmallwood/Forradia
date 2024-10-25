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
            _.mobMovement.Update();
        }

        protected override void RenderDerived()
        {
            _.worldView.Render();
            //_.attackDirection.Render();
        }
    }
}
