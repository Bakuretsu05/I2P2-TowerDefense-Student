#include <functional>
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
void WinScene::BackOnClick(int stage) {
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
