# pragma once
# include "Main.hpp"

class Title : public App::Scene
{
public:

    Title(const InitData& init);
    ~Title();
    void update() override;
    void draw() const override;
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
