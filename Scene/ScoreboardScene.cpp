#include "ScoreboardScene.hpp"
#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

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

static bool CompareScoreBoard(ScoreData& a, ScoreData& b){
    return a.score > b.score;
}

void ScoreboardScene::Initialize() {
    scores.clear();
    while (currentlyShowedScores.empty() == false){
        currentlyShowedScores.pop();
    }

    current_page = 1;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;

    const int vertical_const = 100;
    current_page = 0;
    getScoresFromTxt("Resource/scoreboard.txt");

    // * Sort the scores
    sort(scores.begin(), scores.end(), CompareScoreBoard);

    AddNewObject(new Engine::Label("Scoreboard", "pirulen.ttf", 50, halfW, halfH / 5 - 30, 10, 255, 255, 255, 0.5, 0.5));

    // draw score
    drawScore();

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200,( halfH * 3 / 2 - 50) + vertical_const, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, (halfH * 3 / 2) + vertical_const, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 300,( halfH * 3 / 2 - 50) + vertical_const, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::incCurrentPage, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Next Page", "pirulen.ttf", 48, halfW + 500, (halfH * 3 / 2) + vertical_const, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 700,( halfH * 3 / 2 - 50) + vertical_const, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::decCurrentPage, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Prev Page", "pirulen.ttf", 48, halfW - 500, (halfH * 3 / 2) + vertical_const, 0, 0, 0, 255, 0.5, 0.5));
}

void ScoreboardScene::Terminate() {
    IScene::Terminate();
}

void ScoreboardScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void ScoreboardScene::drawScore() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    // remove all the previous score objects
    while(!currentlyShowedScores.empty()) {
        RemoveObject(currentlyShowedScores.top()->GetObjectIterator());
        currentlyShowedScores.pop();
    }

    for(int i = current_page * SCORES_PER_PAGE; i < scores.size() && i < (current_page + 1) * SCORES_PER_PAGE; i++) {
        std::stringstream buff;
        buff << scores[i].name << " " << scores[i].score << " ... <" << scores[i].date << ">";
        std::string displayData;
        std::getline(buff, displayData);

        Engine::IObject* curr = new Engine::Label(displayData, "pirulen.ttf", 35, halfW, (i % SCORES_PER_PAGE * 50) + 100, 0, 230, 0, 255, 0.5, 0.5);
        AddNewObject(curr);
        currentlyShowedScores.push(curr);
    }
}

void ScoreboardScene::incCurrentPage(int _) { 
    if((current_page + 1) * SCORES_PER_PAGE + 1 <= scores.size()) {
        ++(ScoreboardScene::current_page); 
        drawScore();
        Engine::LOG(Engine::INFO) << "Page incremented! page = " << ScoreboardScene::current_page;
    }
}

void ScoreboardScene::decCurrentPage(int _) { 
    if(current_page > 0) {
        --(ScoreboardScene::current_page); 
        drawScore();
        Engine::LOG(Engine::INFO) << "Page decremented! page = " << ScoreboardScene::current_page;
    }
}

// The format of the .txt => {name} {score} {life} {time_spent} {date: yyyy-mm-dd}
void ScoreboardScene::getScoresFromTxt(const std::string& file_path) {
    std::ifstream scoresF; 
    scoresF.open(file_path);
    scores.clear();

    if(scoresF.is_open()) {
        int i = 1;
        int halfW = Engine::GameEngine::GetInstance().GetScreenSize().x / 2;
        while(scoresF.peek() != EOF) {
            std::string name;
            int score;
            int life;
            std::string date;

            scoresF >> name >> score >> life >> date;

            std::cout << "<======================>" << std::endl;
            std::cout << "name: " << name << std::endl;
            std::cout << "score: " << score << std::endl;
            std::cout << "life: " << life << std::endl;
            std::cout << "date: " << date << std::endl << std::endl;

            if(name.size() == 0) continue;

            ScoreData newData{name, score, life, date};
            scores.push_back(newData);
        }
        scoresF.close();
    }
    else Engine::LOG(Engine::ERROR) << "Failed to open \"" << file_path << "\'"; 
}

