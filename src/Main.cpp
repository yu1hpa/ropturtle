# include "Main.hpp"
# include "Title.hpp"
# include "Game.hpp"


void Main()
{
    Scene::SetResizeMode(ResizeMode::Keep);
    Window::Resize(1024, 768);
    FontAsset::Register(U"TitleFont", 60, Typeface::Heavy);

    App manager;

    manager.add<Title>(U"Title");
    manager.add<Game>(U"Game");
    manager.init(U"Game");
    while (System::Update())
    {
        if (not manager.update())
        {
            break;
        }
    }
}
