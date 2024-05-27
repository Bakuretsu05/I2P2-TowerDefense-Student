#include <string>
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Resources.hpp"

#include "RegenerationEnemy.hpp"

float cooldown = 10.f;
int initialHealth = 0;
RegenerationEnemy::RegenerationEnemy(int x, int y) : Enemy("play/RegenEnemy-1.png", x, y, 10, 50, 5, 5) {
    initialHealth = this->hp;
	for (int i = 1; i <= 4; i++) {
		bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/RegenEnemy-" + std::to_string(i) + ".png"));
	}
}

void RegenerationEnemy::Update(float deltaTime) {
    Enemy::Update(deltaTime);

    if (cooldown >= 0.f){
        cooldown -= 1.0f * deltaTime;
    } else if (cooldown >= -1.f){
        // * do health regen here
        this->hp = hp + 5;
        if (this->hp > initialHealth) this->hp = initialHealth;
        cooldown = 10.0f;
    }

    if (this->hp > initialHealth * 0.75) bmp = bmps[0];
    else if (this->hp > initialHealth * 0.5) bmp = bmps[1];
    else if (this->hp > initialHealth * 0.25) bmp = bmps[2];
    else bmp = bmps[3];
}

