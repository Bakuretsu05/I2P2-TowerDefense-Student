#include <allegro5/base.h>
#include <random>
#include <string>

#include "UI/Animation/DirtyEffect.hpp"
#include "Enemy/Enemy.hpp"
#include "SplashBullet.hpp"
#include "FireBullet.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

class Turret;

SplashBullet::SplashBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
	Bullet("play/bullet-7.png", 500, 1, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}

void SplashBullet::OnExplode(Enemy* enemy) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
	getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-1.png", dist(rng), enemy->Position.x, enemy->Position.y));

    // fire 5 bullets from origin
    for(int i = 1; i <= 5; i++) {
        Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2.5*i), sin(Rotation - ALLEGRO_PI / 2.5*i));
        float rotation = atan2(diff.y, diff.x);
        Engine::Point normalized = diff.Normalize();

        // Change bullet position 
        getPlayScene()->BulletGroup->AddNewObject(new FireBullet(Position + normalized * 36, diff, rotation, nullptr));
    }
}

