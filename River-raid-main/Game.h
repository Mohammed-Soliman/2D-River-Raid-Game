#pragma once
#include <memory>
#include <string>
#include <vector>
#include "CMUgraphicsLib/CMUgraphics.h"
#include "GameObject.h"
#include "Bullet.h"

// Forward declarations
class Background;
class Plane;
class Tank;
class Bridge;
class FuelDepot;
class Enemy;
class Helicopter;
class Jet;
class statusbar;

using namespace std;

class Game
{
protected:
    window* pWind;        // Pointer to the CMU graphics window
    Background* gameground;
    Plane* gamePlane;
    Enemy* gameEnemies;
    int playerLives;
    int playerFuel;
    int stamina;
    int score;
    int enemySpeed;
    int backgroundSpeed;
    int fuelDepotSpeed;  // Speed for fuel depots
    double enemySpawnDelay;
    vector<Background*> backgrounds;
    vector<Enemy*> shapes;
    vector<FuelDepot*> fuelDepots;
    vector<Bullet*> bullets;
    double fuelDepotSpawnDelay;
    int bulletCooldown;
    int currentBulletCooldown;
    bool isPaused;        // New variable for pause state
    bool escapePressed;   // To handle escape key state

public:
    Game();
    ~Game();

    window* getWind() const;
    int getEnemySpeed() const;
    int getBackgroundSpeed() const;
    int getFuelDepotSpeed() const;

    void CreateWind(int, int, int, int) const;
    void go();
    void ClearWindow();
    void GenerateRandomEnemies();
    void SpawnFuelDepots();
    void UpdateFuelDepots();
    void FireBullet();
    void Update();
    bool CheckCollision(const GameObject& obj1, const GameObject& obj2) const;
    void Draw();
	void drawBackground();
    void MoveBackground();
    void saveGame() const;
    void GameOver();
    void loadGame();
    void togglePause();   // New function to toggle pause state
	void PlaySound();
};
