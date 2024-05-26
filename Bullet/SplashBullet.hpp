#ifndef SPLASHBULLET_HPP
#define SPLASHBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class SplashBullet : public Bullet {
public:
	explicit SplashBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Enemy* enemy) override;
};
#endif // SPLASHBULLET_HPP
