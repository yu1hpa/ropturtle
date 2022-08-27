#include "Game.hpp"
#include "ReadFromFile.hpp"

/*TODO
 *ReadFromFile1のReaderに渡す文字列を
 *SharedDataで共有し、画面遷移をおこなう処理を追加
 *
 *Reader -> Parser -> RopElementに格納 -> 描画（ここ）
 */
Game::Game(const InitData& init)
    : IScene{ init }
{
    ClearPrint();
    Print << U"Game::Game()";
    ReadFromFile rf;
    rf.Reader(U"roptext/00.txt");
}

Game::~Game() {
    Print << U"Game::~Game()";
}

void Game::update() {
    if (MouseL.down()) {
        changeScene(U"Title");
    }
}

void Game::draw() const {
    //Rect{ 20, 40, 400, 100 }.draw();
    Rect{ Scene::Width()/2+50, Scene::Height()-50, 340, 50 }.draw();
}
