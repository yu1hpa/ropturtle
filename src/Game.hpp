# pragma once
# include "Main.hpp"

class Game : public App::Scene
{
public:
    
    Game(const InitData& init);
    ~Game();
    void update() override;
    void draw() const override;
private:
    Texture m_texture;
};
