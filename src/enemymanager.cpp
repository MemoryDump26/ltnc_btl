#include "enemymanager.h"

namespace {
    int START_SPAWN_RATE = 5000;
    int THRESHOLD = 2000;
    int MAX_SPAWN_RATE = 500;
}

EnemyManager::EnemyManager(Graphics* _graphics, TextureData* data) :
    graphics(_graphics),
    d(data),
    spawnRate(START_SPAWN_RATE)
{
    //spawnTimer.start();
};

EnemyManager::~EnemyManager() {};

void EnemyManager::update(const Vector2* player) {

    for (size_t i = 0; i < enemies.size(); i++) {
        enemies[i]->update(player);
        if (enemies[i]->state == DIED && enemies[i]->isDead) {
            delete enemies[i];
            enemies.erase(enemies.begin()+i);
            i--;
        }
        else {
            enemies[i]->draw();
        }
    }

    if (spawnTimer.isPausing() == false &&
        spawnTimer.getTime() > spawnRate)
    {
        float spawnX = rand() % 1520 + 200;
        float spawnY = rand() % 680 + 200;
        Enemy* tmp = new Enemy(graphics, d, {spawnX, spawnY});
        enemies.push_back(tmp);
        spawnTimer.start();
    }
}

void EnemyManager::reset() {
    spawnRate = START_SPAWN_RATE;
    for (size_t i = 0; i < enemies.size(); i++) {
        delete enemies[i];
        enemies.erase(enemies.begin()+i);
        i--;
    }
};


void EnemyManager::setSpawnRate(int _spawnRate) {
    spawnRate = _spawnRate;
}

void EnemyManager::incSpawnRate() {
    if (spawnRate > THRESHOLD) spawnRate -= 500;
    else if(spawnRate > MAX_SPAWN_RATE) spawnRate -= 100;
    printf("Spawnrate increased: %d\n", spawnRate);
}

void EnemyManager::startSpawn() {spawnTimer.start();}
void EnemyManager::stopSpawn() {spawnTimer.stop();}
