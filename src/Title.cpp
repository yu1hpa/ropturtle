# include "Title.hpp"

GameStage::GameStage()
    : m_pathCount(0)
{
    for (const auto& path : FileSystem::DirectoryContents(U"roptext/", Recursive::No))
    {
        Console << path;
        m_pathCount++;
    }
}

Title::Title(const InitData& init) : IScene{ init } {
    Print << U"Title::Title()";
}

Title::~Title() {
    Print << U"Title::~Title()";
}

void Title::update() {
    if (MouseL.down())
    {
        changeScene(U"Game");
    }
}

void Title::draw() const {
    static GameStage gamestage;
    Scene::SetBackground(ColorF{ 0.3, 0.4, 0.5 });

    FontAsset(U"TitleFont")(U"My Game").drawAt(400, 100);

    Circle{ Cursor::Pos(), 50 }.draw(Palette::Orange);
    
    for (auto i : step(gamestage.getPathCount()))
    {
        Circle{30+100*i, Scene::Height()/2, 20 }.draw();
    }
}
