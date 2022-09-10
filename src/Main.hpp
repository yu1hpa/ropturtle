# pragma once
# include <Siv3D.hpp>

struct GameData {
    String selectedLevel = U"0";
};

using App = SceneManager<String, GameData>;
