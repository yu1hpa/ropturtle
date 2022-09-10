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

Title::Title(const InitData& init)
    : IScene{ init }
    , m_selectedStage(0)
{
    GameStage gs;
    stageNum = gs.getPathCount();
    font.addFallback(fontEmoji);
}

Title::~Title() {
    Print << U"Title::~Title()";
}

void Title::update() {
    m_startTransition.update(m_startButton.mouseOver());
    
    if (KeyLeft.down())
    {
        if (m_selectedStage > 0)
        {
            m_selectedStage--;
        } else {
            m_selectedStage = stageNum - 1;
        }
    }

    if (KeyRight.down())
    {
        if (m_selectedStage < stageNum - 1)
        {
            m_selectedStage++;
        } else {
            m_selectedStage = 0;
        }
    }
    
    if (m_startButton.leftClicked())
    {
        // int -> std::string -> String型に変換（選ばれたレベルを選択）
        getData().selectedLevel = Unicode::Widen(std::to_string(m_selectedStage));
        changeScene(U"Game");
    }
}

void Title::draw() const {
    static GameStage gamestage;
    Scene::SetBackground(ColorF{ 0.8, 0.8, 0.8 });
    for (auto i : step(10))
    {
        Rect{ 0, (i * 60), 800, 30 }.draw(ColorF{ 0.9, 0.9, 0.9 });
    }

    FontAsset(U"TitleFont")(U"ROP TURTLE").drawAt(titleCenter.movedBy(4, 4), ColorF{ 0.0, 0.5 });
    FontAsset(U"TitleFont")(U"ROP TURTLE").drawAt(Scene::Width()/2, Scene::Height()/4, ColorF{ 1.0, 0.5, 0.0 });

    size_t circleR = 20;
    size_t circle = circleR + 10;
    size_t atLeastLevelNum = 6;
    size_t gamestages = gamestage.getPathCount();
    if (atLeastLevelNum > gamestages)
    {
        for (size_t i : step(6))
        {
            if (i >= gamestages)
            {
                // 工事中のステージ
                Circle{ circle*2 + (Scene::Width() - (circle * 2 + ((6-1)*circleR)))/5 * i, Scene::Height()/2, circleR }.draw(ColorF{ 0.25 });
                font(U"🚧").drawAt(circle*2 + (Scene::Width() - (circle * 2 + ((6-1)*circleR)))/5 * i, Scene::Height()/2 + 20);
            } else {
                // 選択しているステージの表示
                if (i == m_selectedStage)
                {
                    Circle{ circle*2 + (Scene::Width() - (circle * 2 + ((6-1)*circleR)))/5 * i, Scene::Height()/2, circleR }.draw(ColorF{ 0.8, 0, 0});
                } else {
                    Circle{ circle*2 + (Scene::Width() - (circle * 2 + ((6-1)*circleR)))/5 * i, Scene::Height()/2, circleR }.draw();
                }
            }
        }
    } else {
        // ステージ数が6つよりも大きかった場合
    }
    m_startButton.draw(ColorF{1, 0.8, 0.6, m_startTransition.value() }).drawFrame(2, ColorF{0, 0, 0});
    FontAsset(U"Menu")(U"あそぶ").drawAt(m_startButton.center(), ColorF{ 0.2, 0.2, 0.2 });
}
