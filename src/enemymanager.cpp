#include "enemymanager.h"

EnemyManager::EnemyManager(Graphics* _graphics, TextureData* data) :
    graphics(_graphics),
    d(data)
{
    spawnTimer.start();
};

EnemyManager::~EnemyManager() {};

void EnemyManager::update(const Vector2<int>* player) {

    for (size_t i = 0; i < enemies.size(); i++) {
        enemies[i]->update(player);
        if (enemies[i]->hitTimer.isPausing() == true && enemies[i]->isDead) {
            delete enemies[i];
            enemies.erase(enemies.begin()+i);
        }
        else {
            enemies[i]->draw();
        }
    }

    if (spawnTimer.isPausing() == false &&
        spawnTimer.getTime() > spawnRate)
    {
        Enemy* tmp = new Enemy(graphics, d, {rand() % 1920, rand() % 1080});
        enemies.push_back(tmp);
        spawnTimer.start();
    }

}

void EnemyManager::setSpawnRate(int _spawnRate) {
    spawnRate = _spawnRate;
}

void EnemyManager::startSpawn() {spawnTimer.start();}
void EnemyManager::stopSpawn() {spawnTimer.stop();}
