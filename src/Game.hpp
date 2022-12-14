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
    void dispAssembleChain() const;
    void drawCorrect() const;
    void drawIncorrect() const;
private:
    const Font font{ 20, Typeface::Medium };
    const Font ansfont{ 40, Typeface::Medium };
    std::vector<String> instList;
    size_t chosenInst;
    std::vector<String> storedGadget;
    size_t chosenStoredIdx;
    std::vector<String> answer;
    size_t ansInstNum;
    std::vector<String> disp;
    
    bool isCorrect;
    bool isIncorrect;
};
