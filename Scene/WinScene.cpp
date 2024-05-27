#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "WinScene.hpp"
#include "ScoreboardScene.hpp"
#include <fstream>
#include <sstream>

using namespace std;


bool recordingPlayerName = false;
void WinScene::Initialize() {
	ticks = 0;
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH, 0, 0, 0.5, 0.5));
	AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 -10, 255, 255, 255, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
	bgmId = AudioHelper::PlayAudio("win.wav");

	Engine::ImageButton * btnName;
	btnName = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, 150, 400, 75);
	btnName->SetOnClickCallback(std::bind(&WinScene::OnClickNameBtn, this));
	AddNewControlObject(btnName);

	AddNewObject(TXT_Name = new Engine::Label(playerName, "pirulen.ttf", 35, 610, 175, 255, 255, 255, 255, 0.0, 0.0));

}

void WinScene::OnClickNameBtn(){
	cout << "recording player name " << endl;
	recordingPlayerName = true;
}

void WinScene::OnKeyDown(int keyCode){
	cout << "key press " << keyCode << endl;
	if (keyCode == 59 && recordingPlayerName) { //  escape
		recordingPlayerName = false;
	}
	if (!recordingPlayerName) return;

	if (keyCode == 63 && recordingPlayerName){ // backspace
		if (!playerName.empty()){
			playerName.pop_back();
			if (TXT_Name == nullptr) return;
			RemoveObject(TXT_Name->GetObjectIterator());
			AddNewObject(TXT_Name = new Engine::Label(playerName, "pirulen.ttf", 35, 610, 175, 255, 255, 255, 255, 0.0, 0.0));
		}
	}
	// * update player name here
	if (keyCode > 36 || playerName.size() > 11) return;
		for (int i = 0; i < 36; i++){
			if (i == keyCode){
				cout << playerName << endl;
				playerName += '@' + i;

				// * refresh and update text here
				if (TXT_Name == nullptr) return;
				RemoveObject(TXT_Name->GetObjectIterator());
				AddNewObject(TXT_Name = new Engine::Label(playerName, "pirulen.ttf", 35, 610, 175, 255, 255, 255, 255, 0.0, 0.0));
			}
		}
}

void WinScene::Terminate() {
	IScene::Terminate();
	AudioHelper::StopBGM(bgmId);
}
void WinScene::Update(float deltaTime) {
	ticks += deltaTime;
	if (ticks > 4 && ticks < 100 &&
		dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
		ticks = 100;
		bgmId = AudioHelper::PlayBGM("happy.ogg");
	}
}

std::vector<struct ScoreData> getScores(const std::string& filePath) {
    std::ifstream scoresF; 
    scoresF.open(filePath);
    std::vector<struct ScoreData> score_datas;

    if(scoresF.is_open()) {
        int i = 1;
        while(scoresF.peek() != EOF) {
            std::string name;
            int score;
            int life;
            std::string date;

            scoresF >> name >> score >> life >> date;

            ScoreData newData{name, score, life, date};
            score_datas.push_back(newData);
        }
        scoresF.close();
    }

    return score_datas;
}

#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <string>
#include <sstream>
#include "getDate.hpp"

std::string getCurrentDate() {
    // Get the current time as a time_point
    auto now = std::chrono::system_clock::now();

    // Convert to time_t, which represents the time in seconds since epoch
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    // Convert to a tm structure for local time
    std::tm* now_tm = std::localtime(&now_time_t);

    // Extract year, month, day, hours, and minutes
    int year = now_tm->tm_year + 1900; // tm_year is years since 1900
    int month = now_tm->tm_mon + 1;    // tm_mon is months since January (0-11)
    int day = now_tm->tm_mday;
    int hours = now_tm->tm_hour;
    int minutes = now_tm->tm_min;

    std::stringstream buff;

    // Output the date and time
    buff << year << "/" << month << "/" << day << "," << hours << ":" << minutes;

    std::string ret;
    getline(buff, ret);

    return ret;
}

void WinScene::BackOnClick(int stage) {
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
	std::vector<ScoreData> scores = getScores("Resource/scoreboard.txt");

	cout << "playerName: " << playerName << endl;
	cout << "score: " << score << endl;
	cout << "life: " << life << endl;


	ScoreData newData{playerName, score, life, getCurrentDate()};
	scores.push_back(newData);
	cout << "getCurrentDate(): " << newData.date << endl;

	std::ofstream writeF("Resource/scoreboard.txt");
	if(writeF.is_open()) {
		for(auto& data : scores) {
			if(data.name.size() == 0) continue;
            std::cout << "<win ======================>" << std::endl;
            std::cout << "name: " << data.name << std::endl;
            std::cout << "score: " << data.score << std::endl;
            std::cout << "life: " << data.life << std::endl;
            std::cout << "date: " << data.date << std::endl << std::endl;

			if(data.name.size() == 0 || data.date.size() == 0) continue;
			writeF << data.name << " " << data.score << " " << data.life << " " << data.date << endl;
		}
	}

	writeF.close();
}
