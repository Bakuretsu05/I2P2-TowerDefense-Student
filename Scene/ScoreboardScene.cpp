#include "ScoreboardScene.hpp"
#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/Slider.hpp"
#include "Scene/ScoreboardScene.hpp"
#include "Engine/LOG.hpp"

void ScoreboardScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;

    const int vertical_const = 100;
    const int score_perPage = 10;
    std::vector<ScoreboardScene::ScoreData> scores = getScoresFromTxt("Resource/scoreboard.txt");

    AddNewObject(new Engine::Label("Scoreboard", "pirulen.ttf", 50, halfW, halfH / 5 - 30, 10, 255, 255, 255, 0.5, 0.5));

    for(int i = 1; i <= score_perPage; i++) {
        std::stringstream buff;
        buff << scores[i - 1] .name << " " << scores[i - 1].score;
        std::string displayData;
        std::getline(buff, displayData);

        AddNewObject(new Engine::Label(displayData, "pirulen.ttf", 35, halfW, (i * 50) + vertical_const, 0, 230, 0, 255, 0.5, 0.5));
    }

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200,( halfH * 3 / 2 - 50) + vertical_const, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, (halfH * 3 / 2) + vertical_const, 0, 0, 0, 255, 0.5, 0.5));
}

void ScoreboardScene::Terminate() {
    IScene::Terminate();
}

void ScoreboardScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

// The format of the .txt => {name} {score} {life} {time_spent} {date: yyyy-mm-dd}
std::vector<ScoreboardScene::ScoreData> ScoreboardScene::getScoresFromTxt(const std::string& file_path) {
    std::ifstream scoresF; 
    scoresF.open(file_path);
    std::vector<ScoreboardScene::ScoreData> score_datas;

    if(scoresF.is_open()) {
        while(scoresF.peek() != EOF) {
            std::string name;
            int score;
            int life;
            int time_spent;
            std::string date;

            scoresF >> name >> score >> life >> time_spent >> date;

            ScoreboardScene::ScoreData newData{name, score, life, time_spent, Date(date)};
            score_datas.push_back(newData);
        }
        scoresF.close();
    }
    else Engine::LOG(Engine::ERROR) << "Failed to open \"" << file_path << "\'"; 

    return score_datas;
}