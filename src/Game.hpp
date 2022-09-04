# pragma once
# include "Main.hpp"

class Game : public App::Scene
{
public:
    Game(const InitData& init);
    ~Game();
    void update() override;
    void draw() const override;

    void drawInstList() const;
    void drawBlock() const;
    void initStoredGadget();
private:
    const Font font{ 20 };
    std::vector<String> instList;
    size_t chosenInst;
    std::vector<String> storedGadget;
    size_t chosenStoredIdx;
    size_t ansInstNum;
};
