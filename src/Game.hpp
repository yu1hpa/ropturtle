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
    String pickAddress(size_t ci);
    bool isCorrectAnswer();
private:
    const Font font{ 20 };
    std::vector<String> instList;
    size_t chosenInst;
    std::vector<String> storedGadget;
    size_t chosenStoredIdx;
    std::vector<String> answer;
    size_t ansInstNum;
};
