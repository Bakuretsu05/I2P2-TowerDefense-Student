#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/SplashBullet.hpp"
#include "Engine/Group.hpp"
#include "SplashTurret.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int SplashTurret::Price = 150;
SplashTurret::SplashTurret(float x, float y) :
	Turret("play/tower-base.png", "play/SplashTurret.png", x, y, 250, Price, 0.9) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void SplashTurret::CreateBullet() {
	Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	float rotation = atan2(diff.y, diff.x);
	Engine::Point normalized = diff.Normalize();
	// Change bullet position to the front of the gun barrel.
	getPlayScene()->BulletGroup->AddNewObject(new SplashBullet(Position + normalized * 36, diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}
