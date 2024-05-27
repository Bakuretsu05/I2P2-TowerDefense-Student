#ifndef REGENERATIONENEMY_HPP
#define REGENERATIONENEMY_HPP
#include "Enemy.hpp"

class RegenerationEnemy : public Enemy {
private:
	std::vector<std::shared_ptr<ALLEGRO_BITMAP>> bmps;
public:
	RegenerationEnemy(int x, int y);
    void Update(float deltaTime) override;
};
#endif // REGENERATIONENEMY_HPP
