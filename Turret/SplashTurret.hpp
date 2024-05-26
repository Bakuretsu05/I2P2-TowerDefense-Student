#ifndef SPLASHTURRET_HPP
#define SPLASHTURRET_HPP
#include "Turret.hpp"

class SplashTurret: public Turret {
public:
	static const int Price;
    SplashTurret(float x, float y);
	void CreateBullet() override;
};
#endif // SPLASHTURRET_HPP
