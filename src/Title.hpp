# pragma once
# include "Main.hpp"

class Title : public App::Scene
{
public:

    Title(const InitData& init);
    ~Title();
    void update() override;
    void draw() const override;
private:
    size_t m_selectedStage;
    size_t stageNum;
    Rect m_startButton{ Scene::Width()/2 - 150, 3*Scene::Height()/4 + 60, 300, 60 };
    Transition m_startTransition{ 0.4s, 0.2s };
    const Font font{ 20 };
    const Font fontEmoji{ 36, Typeface::ColorEmoji };
    const Vec2 titleCenter{ Scene::Width()/2, Scene::Height()/4 };
};

class GameStage
{
public:
    GameStage();
    size_t getPathCount()
    {
        return m_pathCount;
    }
private:
    size_t m_pathCount;
};
