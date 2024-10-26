namespace YrradiaSDL2.ForradiaTheme.Scenes.WorldGenerationScene
{
    public class WorldGenerationScene : Scene
    {
        public override void OnEnter()
        {
            base.OnEnter();
            _.worldGenerator.GenerateWorld();
            _.sceneManager.GoToScene("MainScene");
        }
        protected override void UpdateDerived()
        {
        }
        protected override void RenderDerived()
        {
        }
    }
}
