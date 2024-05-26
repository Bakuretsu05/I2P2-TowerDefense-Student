#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include <allegro5/allegro_audio.h>
#include "Engine/IScene.hpp"
#include <string>

using namespace std;

class WinScene final : public Engine::IScene {
private:
	float ticks;
	ALLEGRO_SAMPLE_ID bgmId;
public:


	string playerName = "PLAYER";
	IObject * TXT_Name;

	explicit WinScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void BackOnClick(int stage);

	void OnClickNameBtn();

	// void OnMouseDown(int button, int mx, int my) override;
	// void OnMouseMove(int mx, int my) override;
	// void OnMouseUp(int button, int mx, int my) override;
	void OnKeyDown(int keyCode) override;
};

#endif // WINSCENE_HPP
