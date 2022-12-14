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
    , chosenInst(0)
    , chosenStoredIdx(0)
    , isCorrect(false)
    , isIncorrect(false)
{
    ClearPrint();
    ReadFromFile rf;

    String filepath = U"roptext/";
    filepath += getData().selectedLevel;
    filepath += U".txt";
    rf.Reader(filepath);

    disp = rf.getDisp();
    instList = rf.getGadget();

    // 答えの数
    ansInstNum = rf.getAnswer().size();
    // 答え合わせ用のリスト
    answer = rf.getAnswer();

    // 答え分テキストを入れる場所を確保&初期化
    storedGadget.resize(ansInstNum);
    initStoredGadget();
}

Game::~Game() {
}

void Game::update()
{
    if (KeyZ.down())
    {
        changeScene(U"Title");
    }

    /*
     * 命令リスト(InstList)から命令を選ぶ
     * 一番上の要素でJキーを押したときは一番上に、
     * 一番下の要素でKキーを押したときは一番下になる
     */
    if (KeyJ.down())
    {
        if (chosenInst < instList.size() - 1)
        {
            chosenInst += 1;
        } else {
            chosenInst = 0;
        }
    }

    if (KeyK.down())
    {
        if (chosenInst > 0)
        {
            chosenInst -= 1;
        } else {
            chosenInst = instList.size() - 1;
        }
    }

    /* Fキーが押されたとき、
     * ブロックに表示する文字列として使うstoredGadgetに
     * InstList内で選択しているもの(chosenInst)を格納する
     */
    if (KeyF.down())
    {
        if (chosenStoredIdx < ansInstNum)
        {
            storedGadget.at(chosenStoredIdx) = pickAddress(chosenInst);
            chosenStoredIdx++;
        }
    }

    // 答え合わせ
    if (KeyB.down())
    {
        if (storedGadget.at(ansInstNum-1) != U"" )
        {
            // TODO: 答え合わせをするかどうかアラートを入れる（未定）
            if (isCorrectAnswer())
            {
                isCorrect = true;
            } else {
                isIncorrect = true;
            }
        } else {
            Print << U"ブロックを埋めてください";
        }
    }

    // ブロックをクリア
    if (KeyQ.down())
    {
        initStoredGadget();
        chosenStoredIdx = 0;
    }
}

bool Game::isCorrectAnswer()
{
    size_t i = answer.size() - 1;
    for (auto a : answer)
    {
        if (a != storedGadget.at(i))
        {
            return false;
        }
        i--;
    }
    return true;
}

void Game::draw() const
{
    drawBlock();
    drawInstList();
    dispAssembleChain();
    if (isCorrect)
    {
        drawCorrect();
    }
    if (isIncorrect)
    {
        drawIncorrect();
    }
}

String Game::pickAddress(size_t ci)
{
    std::string delimiter = ":";
    String g = instList.at(ci);
    // 値だけの場合(":"が見つからなかったとき)
    if(g.narrow().find(delimiter) == std::string::npos)
    {
        return g;
    } else {
        // 0x401aa0:A
        // ^ Pickup this by this func.
        size_t pos = 0;
        while((pos = g.narrow().find(delimiter)) != std::string::npos)
        {
            // String型で返す(Unicode::Widen)
            return Unicode::Widen(g.narrow().substr(0, pos));
        }
        return U"";
    }
}

void Game::initStoredGadget()
{
    for (auto i : step(ansInstNum))
    {
        storedGadget.at(i) = U"";
    }
}

void Game::drawInstList() const
{
    size_t gi = 0;

    // InstList Field
    Rect{ 50, Scene::Height()/4, Scene::Width()/2 - 50, 3*(Scene::Height()/4) }.draw(ColorF{0.3, 0.3, 0.3, 0.5});
    for(auto g : instList)
    {
        if (gi == chosenInst)
        {
            font(g).draw(60, 10 + Scene::Height()/4+30*gi).drawFrame(2, ColorF{1, 0, 0, 1});
        } else {
            font(g).draw(60, 10 + Scene::Height()/4+30*gi);
        }
        gi++;
    }
}

void Game::drawBlock() const
{
    /*
     画面
     +----------------------------------------------------------+
     |                                                          |
     |                                                          |
     |                                                          |
     |                                                          |
     |                                  rectLeft   rectRight    |
     |                                  v          v            |
     |               ^                ^ +----------+ <rectTop   |
     |               |  rectHeightPad | |   BLOCK  |            |
     | rectStartLine |                v +----------+ <rectButtom|
     |               |                                          |
     |               v                                          |
     +----------------------------------------------------------+
     **/

    // 長方形の左と右の座標を計算
    size_t rectLeft = Scene::Width()/2+50;
    size_t rectRight = rectLeft + 340;
    // 長方形の横の長さを計算
    size_t rectWidth = rectRight - rectLeft;

    size_t rectHeightPadding = 50;

    for(auto i : step(ansInstNum))
    {
        Rect{ rectLeft, Scene::Height() - (75 * (i+1)), 340, rectHeightPadding }.draw();

        //各長方形の上と下の座標を計算
        size_t rectTop = Scene::Height() - (75 * (i+1));
        size_t rectButtom = Scene::Height() - (75 * (i+1)) + rectHeightPadding;

        // 長方形の縦の長さを計算
        size_t rectHeight = rectButtom - rectTop;

        font(storedGadget.at(i)).drawAt(rectLeft + rectWidth/2, rectButtom - rectHeight/2, ColorF{ 0.25 });
    }
    
    //各長方形の上と下の座標を計算
    size_t rectTop = Scene::Height() - (75 * (ansInstNum+1));
    size_t rectButtom = Scene::Height() - (75 * (ansInstNum+1)) + rectHeightPadding;
    // 長方形の縦の長さを計算
    size_t rectHeight = rectButtom - rectTop;
    font(U"v RIP (ROP START HERE)").drawAt(rectLeft + rectWidth/2, rectButtom - rectHeight/2, ColorF{ 0, 0, 0 });
}

void Game::dispAssembleChain() const
{
    Rect{ 50, 50, Scene::Width()/2 - 50, 50 }.draw(ColorF{ 0.6, 0.8, 1, 80 });
    font(disp.at(0)).drawAt(50 + (Scene::Width()/2 - 2*50)/2, 50+(50/2), ColorF{ 0, 0, 0 });
}

void Game::drawCorrect() const
{
    Rect{ 0, 0, Scene::Width(), Scene::Height() }.draw(ColorF{ 0.7, 0.7, 0.7, 0.5 });
    ansfont(U"Correct !!!").drawAt(Scene::Width()/2, Scene::Height()/2, ColorF{ 1, 0.1, 0.1 });
}

void Game::drawIncorrect() const
{
    Rect{ 0, 0, Scene::Width(), Scene::Height() }.draw(ColorF{ 0.7, 0.7, 0.7, 0.5 });
    ansfont(U"Incorrect...").drawAt(Scene::Width()/2, Scene::Height()/2, ColorF{ 0.1, 0.1, 1 });
}
