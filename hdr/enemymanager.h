#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "vector2d.h"
#include "enemy.h"
#include "timer.h"

class EnemyManager {
public:
    EnemyManager(Graphics* _graphics, TextureData* data);
    ~EnemyManager();
    void update(const Vector2* player);
    void clear();
    void setSpawnRate(int _spawnRate);
    void startSpawn();
    void stopSpawn();
    std::vector<Enemy*> enemies;

private:
    Graphics* graphics;
    TextureData* d;
    int spawnRate = 5000;
    Timer spawnTimer;

};

#endif
