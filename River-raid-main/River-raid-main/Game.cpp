#include "Game.h"
#include "Toolbar.h"
#include "Background.h"
#include "Tree.h"
#include "FuelDepot.h"
#include "GameConfig.h"
#include "Helicopter.h"
#include "Plane.h"
#include "Bridge.h"
#include "Enemy.h"
#include "Tank.h"
#include "Jet.h"
#include "Bullet.h"
#include <iostream>
#include <windows.h>  // for Sleep() and GetAsyncKeyState()
#include "CMUgraphicsLib/CMUgraphics.h"
#include "CMUgraphicsLib/auxil.h"
#include <random>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "GameConfig.h"
#include <algorithm>  
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")

enum Enemies_ships { JET, HELICOPTER, TANK };

Game::Game() : playerLives(3), playerFuel(100), stamina(100), score(0), enemySpeed(2), enemySpawnDelay(5.0), backgroundSpeed(2), fuelDepotSpawnDelay(8.0), bulletCooldown(10), currentBulletCooldown(0), fuelDepotSpeed(0), isPaused(false), escapePressed(false) {
	// Initialize random seed once
	srand(static_cast<unsigned int>(time(nullptr)));
	
	// Create the window
	pWind = new window(config.windowWidth, config.windowHeight, 5, 5);
	// Initialize game objects
	gamePlane = new Plane(this, { config.windowWidth/2, config.windowHeight - 100 }, 50, 80, BLUE, BLUE);
	gameground = nullptr;
	gameEnemies = nullptr;
}

window* Game::getWind() const
{
	return pWind;
}

int Game::getEnemySpeed() const
{
	return enemySpeed;
}

int Game::getBackgroundSpeed() const
{
	return backgroundSpeed;
}

int Game::getFuelDepotSpeed() const {
	return fuelDepotSpeed;
}

Game::~Game()
{
	// Clean up game objects
	delete gamePlane;
	delete gameground;
	delete gameEnemies;
	
	// Clean up vectors
	for (auto* bg : backgrounds) {
		delete bg;
	}
	backgrounds.clear();
	
	for (auto* shape : shapes) {
		delete shape;
	}
	shapes.clear();

	for (auto* depot : fuelDepots) {
		delete depot;
	}
	fuelDepots.clear();
	
	for (auto* bullet : bullets) {
		delete bullet;
	}
	bullets.clear();
	
	// Clean up window last
	delete pWind;
}

//clicktype Game::getMouseClick(int& x, int& y) const
//{
//    //return pWind->WaitMouseClick(x, y);
//}
//
//std::string Game::getSrting() const
//{
//    std::string Label;
//    char         Key;
//    keytype      ktype;
//    //pWind->FlushKeyQueue();
//    while (true)
//    {
//      /*  ktype = pWind->WaitKeyPress(Key);*/
//        if (ktype == ESCAPE) return "";
//        if (Key == 13)     return Label;
//        if (Key == 8 && !Label.empty()) Label.pop_back();
//        else if (Key != 8)             Label.push_back(Key);
//        printMessage(Label);
//    }
//}
//
void Game::CreateWind(int w, int h, int x, int y) const
{
	if (pWind) {
		pWind->SetBrush(config.bkGrndColor);
		pWind->SetPen(config.bkGrndColor, 1);
		pWind->DrawRectangle(0, 0, w, h);
	}
}

//void Game::clearStatusBar() const
//{
//    pWind->SetPen(config.statusBarColor, 1);
//    pWind->SetBrush(config.statusBarColor);
//    pWind->DrawRectangle(
//        0,
//        config.windHeight - config.statusBarHeight,
//        config.windWidth,
//        config.windHeight
//    );
//}

//void Game::printMessage(std::string msg) const
//{
//    clearStatusBar();
//    pWind->SetPen(config.penColor, 50);
//    pWind->SetFont(24, BOLD, BY_NAME, "Arial");
//    pWind->DrawString(
//        10,
//        config.windHeight - static_cast<int>(0.85 * config.statusBarHeight),
//        msg
//    );
//}

const double ratio = config.ratio;

void Game::drawBackground() 
{
	// Draw the three background rectangles
	const int leftWidth = static_cast<int>(config.windowWidth * config.ratio);
	const int rightStart = static_cast<int>(config.windowWidth * (1 - config.ratio));

	// Left gray area
	pWind->SetPen(BLACK, 1);
	pWind->SetBrush(DARKGREEN);
	pWind->DrawRectangle(0, 0, leftWidth, config.windowHeight, FILLED);

	// Right gray area
	pWind->DrawRectangle(rightStart, 0, config.windowWidth, config.windowHeight, FILLED);

	// Center blue area (play area)
	pWind->SetPen(BLUE, 1);
	pWind->SetBrush(BLUE);
	pWind->DrawRectangle(leftWidth, 0, rightStart, config.windowHeight, FILLED);
}

void Game::ClearWindow()
{


	// Draw the three background rectangles
	const int leftWidth = static_cast<int>(config.windowWidth * config.ratio);
	const int rightStart = static_cast<int>(config.windowWidth * (1 - config.ratio));

	// Left gray area
	pWind->SetPen(BLACK, 1);
	pWind->SetBrush(DARKGREEN);
	pWind->DrawRectangle(0, 0, leftWidth, config.windowHeight, FILLED);

	// Right gray area
	pWind->DrawRectangle(rightStart, 0, config.windowWidth, config.windowHeight, FILLED);

	// Center blue area (play area)
	pWind->SetPen(BLUE, 1);
	pWind->SetBrush(BLUE);
	pWind->DrawRectangle(leftWidth, 0, rightStart, config.windowHeight, FILLED);
}

void Game::MoveBackground()
{
	// Adjust background speed based on fuel amount
	backgroundSpeed = (playerFuel > 0) ? static_cast<int>((playerFuel / 100.0) * 5) + 1 : 2;

	// Consume fuel while moving
	static int fuelConsumptionCounter = 0;
	if (++fuelConsumptionCounter >= 30) {
		if (playerFuel > 0) {
			playerFuel--;
		}
		fuelConsumptionCounter = 0;
	}

	// If no fuel, reduce speed to 0 and potentially lose a life
	if (playerFuel <= 0) {
		stamina--;
		if (playerLives > 0) {
			playerFuel = 100; // Refill fuel when losing a life
		}
		return;
	}

	// Move existing background objects
	for (auto it = backgrounds.begin(); it != backgrounds.end();) {
		Background* bg = *it;
		if (bg) {
			bg->move();  // Move the object
			bg->draw();  // Draw the object
			
			// Remove if out of screen
			if (bg->getY() > config.windowHeight) {
				delete bg;
				it = backgrounds.erase(it);
			} else {
				++it;
			}
		} else {
			it = backgrounds.erase(it);
		}
	}

	// Spawn new background objects
	static time_t lastSpawnTime = time(0);
	time_t now = time(0);
	double delay = 2.0;

	// Only spawn if we have less than the maximum number of objects
	if (backgrounds.size() < 10 && difftime(now, lastSpawnTime) >= delay) {
		int choice = rand() % 2;  // 0 for Tree, 1 for Bridge
		Background* newBackground = nullptr;

	if (choice == 0) // Tree
	{
		delay = 4.0; // Increase delay for trees
			// Create new tree
			newBackground = new Tree(this, {0,50}, 50, 80, GREEN ,BROWN, GREEN);
			
	}
	else // Bridge
	{
		delay = 10.0;
			int bridgeWidth = config.windowWidth - config.ratio * config.windowWidth;
			newBackground = new Bridge(this, {(int)config.ratio * config.windowWidth,50}, bridgeWidth, 50, GRAY, GREEN);
			
		}

		
		// Add to background objects
		backgrounds.push_back(newBackground);
		lastSpawnTime = now;
	}
}

void Game::GenerateRandomEnemies()
{
	static time_t lastSpawnTime = time(0);
	time_t now = time(0);

	// Calculate spawn delay based on score
	double baseDelay = 5.0;
	double minDelay = 1.0;  // Minimum delay between spawns
	double scoreEffect = score / 1000.0;  // Every 1000 points reduces delay
	double currentDelay = (baseDelay - scoreEffect > minDelay) ? baseDelay - scoreEffect : minDelay;

	// Calculate enemy speed based on score
	int baseSpeed = 2;
	int maxSpeed = 15;
	int speedIncrease = score / 500;  // Every 500 points increases speed
	enemySpeed = (baseSpeed + speedIncrease < maxSpeed) ? baseSpeed + speedIncrease : maxSpeed;

	if (difftime(now, lastSpawnTime) >= currentDelay)
	{
		// Increase chance of multiple enemies spawning at higher scores
		int maxEnemiesPerSpawn = 1 + (score / 2000);  // Every 2000 points allows one more enemy
		int enemiesToSpawn = 1 + (rand() % maxEnemiesPerSpawn);

		for(int i = 0; i < enemiesToSpawn; i++)
		{
			int shapeType = rand() % 3;
			Enemy* newShape = nullptr;

			if (shapeType == JET) // Jet
			{
				newShape = new Jet(this, {0,50}, 50, 80, BLACK, BLACK, BLACK, BLACK);
			}
			else if (shapeType == HELICOPTER) // Helicopter
			{
				newShape = new Helicopter(this, { 0,50 }, 100, 50, BLACK, YELLOW, DARKOLIVEGREEN, YELLOW);
			}
			else if (shapeType == TANK) // Tank
			{
				newShape = new Tank(this, { 0,50 }, 110, 40, BLACK, BLUE, RED, GREEN);
			}

	
				for (auto& shape : shapes)
				{
					if (dynamic_cast<Jet*>(shape))
					{

						playerFuel--;
					}
				}
				shapes.push_back(newShape);
			
		}
		lastSpawnTime = now;
	}
	//festure 29
	// Move and draw existing enemies
	for (auto& shape : shapes)
	{
		if (shape) {
			shape->move();
			shape->draw();
		}
	}

	// Remove enemies that are out of bounds
	shapes.erase(remove_if(shapes.begin(), shapes.end(),
		[&](Enemy* shape) {
			bool shouldRemove = false;
			if (shape) {
				if (dynamic_cast<Jet*>(shape)) {
					// Remove jets that have moved off the screen horizontally
					shouldRemove = (shape->getX() < -shape->getWidth() || 
								  shape->getX() > config.windowWidth);
				} else {
					// Remove other enemies that have moved off the bottom
					shouldRemove = (shape->getY() > config.windowHeight);
				}
				
				if (shouldRemove) {
					delete shape;
				}
			}
			return shouldRemove;
		}), shapes.end());
}

void Game::SpawnFuelDepots() {
	static time_t lastSpawnTime = time(0);
	time_t now = time(0);

	// Spawn more frequently when fuel is low
	double spawnDelay = (playerFuel < 30) ? 3.0 : 8.0;

	// Only spawn if enough time has passed and we have space
	if (difftime(now, lastSpawnTime) >= spawnDelay && fuelDepots.size() < 3) {
		// Calculate spawn position
		const int depotWidth = 60;
		const int depotHeight = 40;
		const int min = (int)(config.windowWidth * config.ratio);  // 20% from left
		const int max = (int)(config.windowWidth * (1 - config.ratio) - depotWidth);  // 80% from left minus depot width
		int x = min + rand() % (max - min);
		
		// Create and initialize new fuel depot
		FuelDepot* newDepot = new FuelDepot(this, {x, 0}, depotWidth, depotHeight, BLACK, YELLOW);  // Changed Y from 50 to 0
		fuelDepots.push_back(newDepot);
		lastSpawnTime = now;
	}
}

void Game::UpdateFuelDepots() {
	
	auto it = fuelDepots.begin();
	while (it != fuelDepots.end()) {
		FuelDepot* depot = *it;
		bool shouldDelete = false;
		
		if (depot) {
			
			depot->move();
			
			
			depot->draw();
			
			
			if (gamePlane && CheckCollision(*gamePlane, *depot)) {
				// Increase fuel with cap at 100
				playerFuel = (playerFuel + 30 > 100) ? 100 : playerFuel + 30;
				shouldDelete = true;
			}
			
			else if (depot->getY() > config.windowHeight) {
				shouldDelete = true;
			}
			
		
			if (shouldDelete) {
				delete depot;
				it = fuelDepots.erase(it);
			} else {
				++it;
			}
		} else {
			// Remove null pointers
			it = fuelDepots.erase(it);
		}
	}
}


void Game::Update()
{
	if (isPaused) return;

	// Check fuel and lives first
	if (playerFuel <= 0) {
		playerLives--;  // Decrease lives by 1
		playerFuel = 100;  // Reset fuel to 100
		
		// Check if game is over
		if (playerLives <= 0) {
			GameOver();
			return;
		}
	}

	// Handle bullet cooldown and firing
	if (currentBulletCooldown > 0) {
		currentBulletCooldown--;
	}

	// Check for spacebar press to fire bullet
	if (pWind && currentBulletCooldown == 0) {
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			FireBullet();
		}
	}

	// Update and check bullet collisions
	for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
		Bullet* bullet = *bulletIt;
		bool bulletHit = false;

		if (bullet) {
			bullet->move();
			
			// Check collision with enemies
			for (auto enemyIt = shapes.begin(); enemyIt != shapes.end() && !bulletHit;) {
				Enemy* enemy = *enemyIt;
				if (enemy && CheckCollision(*bullet, *enemy)) {
					// Increase score based on enemy type
					if (dynamic_cast<Jet*>(enemy)) {
						score += 100;
					} else if (dynamic_cast<Tank*>(enemy)) {
						score += 30;
					} else if (dynamic_cast<Helicopter*>(enemy)) {
						score += 60;
					}

					// Remove the enemy
					delete enemy;
					enemyIt = shapes.erase(enemyIt);
					bulletHit = true;
				} else {
					++enemyIt;
				}
			}
			// Check collision with fuel depots
			for (auto depotIt = fuelDepots.begin(); depotIt != fuelDepots.end() && !bulletHit;) {
				FuelDepot* depot = *depotIt;
				if (depot && CheckCollision(*bullet, *depot)) {
					// Remove both bullet and fuel depot
					delete depot;
					depotIt = fuelDepots.erase(depotIt);
				}
				else {
					++depotIt;
				}
			}

			// Check collision with bridges
			for (auto bgIt = backgrounds.begin(); bgIt != backgrounds.end() && !bulletHit;) {
				Background* bg = *bgIt;
				if (bg && dynamic_cast<Bridge*>(bg) && CheckCollision(*bullet, *bg)) {
					score += 500;
					delete bg;
					bgIt = backgrounds.erase(bgIt);
					bulletHit = true;
				} else {
					++bgIt;
				}
			}

			// Remove bullet if it hit something or went off screen
			if (bulletHit) {
				if (bullet) {
					delete bullet;
					bullet = nullptr;
				}
				bulletIt = bullets.erase(bulletIt);
			} else {
				bullet->draw();  // Draw the bullet if it's still active
				++bulletIt;
			}
		} else {
			bulletIt = bullets.erase(bulletIt);
		}
	}

	// Check collisions between plane and enemies
	if (gamePlane) {
		// Check collisions with enemies
		for (auto it = shapes.begin(); it != shapes.end();) {
			Enemy* enemy = *it;
			if (enemy && CheckCollision(*gamePlane, *enemy)) {
				// Decrease stamina based on collision
				stamina = (stamina > 15) ? stamina - 15 : 0;
				
				// Remove the enemy
				delete enemy;
				it = shapes.erase(it);
				
				// Check if stamina is depleted
				if (stamina <= 0) {
					playerLives--;
					if (playerLives > 0) {
						stamina = 100; // Reset stamina if still alive
					}
				}
			} else {
				++it;
			}
		}

		// Check collisions with background objects (bridges)
		for (auto it = backgrounds.begin(); it != backgrounds.end();) {
			Background* bg = *it;
			if (bg && dynamic_cast<Bridge*>(bg) && CheckCollision(*gamePlane, *bg)) {
				// Decrease stamina for bridge collision
				stamina = (stamina > 50) ? stamina - 50 : 0;
				
				// Remove the bridge
				delete bg;
				it = backgrounds.erase(it);
				
				// Check if stamina is depleted
				if (stamina <= 0) {
					playerLives--;
					if (playerLives > 0) {
						stamina = 100; // Reset stamina if still alive
					}
				}
			} else {
				++it;
			}
		}
	}

	// Update fuel depots separately
	auto depotIt = fuelDepots.begin();
	while (depotIt != fuelDepots.end()) {
		FuelDepot* depot = *depotIt;
		bool shouldDelete = false;
		
		if (depot) {
			depot->move();
			depot->draw();
			
			// Only check plane collision with fuel depots
			if (gamePlane && CheckCollision(*gamePlane, *depot)) {
				playerFuel = (playerFuel + 30 > 100) ? 100 : playerFuel + 30;
				shouldDelete = true;
			}
			else if (depot->getY() > config.windowHeight) {
				shouldDelete = true;
			}
			
			if (shouldDelete) {
				delete depot;
				depotIt = fuelDepots.erase(depotIt);
			} else {
				++depotIt;
			}
		} else {
			depotIt = fuelDepots.erase(depotIt);
		}
	}

	// Update backgrounds
	for (auto it = backgrounds.begin(); it != backgrounds.end();) {
		Background* bg = *it;
		if (bg) {
			bg->move();
			if (bg->getY() > config.windowHeight) {
				delete bg;
				it = backgrounds.erase(it);
			} else {
				++it;
			}
		} else {
			it = backgrounds.erase(it);
		}
	}

	// Increase difficulty
	if (enemySpawnDelay > 1.0) enemySpawnDelay -= 0.01;
	if (enemySpeed < 15) enemySpeed++;

	// Update fuel depot speed based on enemy and background speed
	fuelDepotSpeed = enemySpeed - backgroundSpeed;
	if (fuelDepotSpeed < 1) fuelDepotSpeed = 1; // Ensure minimum speed of 1
}

bool Game::CheckCollision(const GameObject& obj1, const GameObject& obj2) const
{
		return !(obj1.getX() + obj1.getWidth() < obj2.getX() || // obj1 is to the left of obj2
			obj1.getX() > obj2.getX() + obj2.getWidth() || // obj1 is to the right of obj2
			obj1.getY() + obj1.getHeight() < obj2.getY() || // obj1 is above obj2
			obj1.getY() > obj2.getY() + obj2.getHeight()); // obj1 is below obj2 
}

void Game::Draw()
{
	if (!pWind) return;

	// Draw HUD background
	pWind->SetPen(BLACK);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(10, 10, 200, 130);  // Made taller to accommodate score

	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	
	// Draw lives
	pWind->SetPen(BLACK);
	pWind->DrawString(20, 20, "Lives: " + to_string(playerLives));

	// Draw fuel with color coding
	string fuelStr = "Fuel: " + to_string(playerFuel) + "%";
	if (playerFuel <= 25) {
		pWind->SetPen(RED);
	} else if (playerFuel <= 50) {
		pWind->SetPen(ORANGE);
	} else {
		pWind->SetPen(GREEN);
	}
	pWind->DrawString(20, 45, fuelStr);

	// Draw stamina with color coding
	string staminaStr = "Stamina: " + to_string(stamina) + "%";
	if (stamina <= 25) {
		pWind->SetPen(RED);
	} else if (stamina <= 50) {
		pWind->SetPen(ORANGE);
	} else {
		pWind->SetPen(GREEN);
	}
	pWind->DrawString(20, 70, staminaStr);

	// Draw score
	pWind->SetPen(BLUE);
	pWind->DrawString(20, 95, "Score: " + to_string(score));
}



void Game::GameOver()
{
	// Clear the window
	ClearWindow();

	// Set up the "Game Over" message
	const string gameOverText = "GAME OVER";
	const string scoreText = "Final Score: " + to_string(score);
	const string restartText = "Press R to Restart or Q to Quit";
	int textWidth, textHeight;

	window* pWind = getWind();
	if (pWind) {
		bool waitingForInput = true;
		while (waitingForInput) {
			// Get the size of the "Game Over" text
			pWind->SetFont(50, BOLD, SWISS);
			pWind->GetStringSize(textWidth, textHeight, gameOverText);

			// Calculate the center position for the text
			int centerX = (pWind->GetWidth() - textWidth) / 2;
			int centerY = (pWind->GetHeight() - textHeight) / 2;

			// Display the "Game Over" message
			pWind->SetBrush(color(0, 0, 0)); // Black background
			pWind->DrawRectangle(0, 0, pWind->GetWidth(), pWind->GetHeight());

			pWind->SetPen(color(255, 0, 0)); // Red text
			pWind->DrawString(centerX, centerY, gameOverText);

			// Display score
			pWind->SetFont(30, BOLD, SWISS);
			pWind->GetStringSize(textWidth, textHeight, scoreText);
			centerX = (pWind->GetWidth() - textWidth) / 2;
			pWind->DrawString(centerX, centerY + 60, scoreText);

			// Display restart/quit message
			pWind->SetFont(20, PLAIN, SWISS);
			pWind->DrawString((pWind->GetWidth() - 300) / 2, centerY + 120, restartText);

			pWind->UpdateBuffer();

			// Check for key press
			if (GetAsyncKeyState('R') & 0x8000) {
				// Reset game state
				playerLives = 3;
				playerFuel = 100;
				stamina = 100;
				score = 0;
				enemySpeed = 2;
				enemySpawnDelay = 5.0;
				backgroundSpeed = 2;
				fuelDepotSpawnDelay = 8.0;
				bulletCooldown = 10;
				currentBulletCooldown = 0;

				// Clear all game objects
				for (auto* depot : fuelDepots) delete depot;
				fuelDepots.clear();

				for (auto* bg : backgrounds) delete bg;
				backgrounds.clear();

				for (auto* bullet : bullets) delete bullet;
				bullets.clear();

				for (auto* enemy : shapes) delete enemy;
				shapes.clear();

				// Reset plane position
				if (gamePlane) {
					gamePlane->setX(config.windowWidth/2);
					gamePlane->setY(config.windowHeight - 100);
				}

				

				waitingForInput = false;
			}
			else if (GetAsyncKeyState('Q') & 0x8000) {
				exit(0); // Quit the game
			}

			Pause(50); // Small delay to prevent CPU overuse
		}
	}
}

void Game::FireBullet() {
	if (!gamePlane || currentBulletCooldown > 0) return;

	// Calculate bullet position - adjust these values to match your plane's dimensions
	point bulletPos = { 
		gamePlane->getX() + (gamePlane->getWidth() / 2),  // Center of plane
		gamePlane->getY() - 20  // Above the plane
	};
	
	// Create new bullet with smaller dimensions
	Bullet* newBullet = new Bullet(this, bulletPos, 5, 15, RED, RED);
	bullets.push_back(newBullet);
	
	// Reset cooldown to a smaller value for faster firing
	currentBulletCooldown = 5;  // Reduced from 10 to 5 for more frequent firing
}
void Game::saveGame() const
{
	ofstream saveFile("save.txt");
	if (saveFile.is_open())
	{
		saveFile << gamePlane->getY() << endl;
		saveFile << playerLives << endl;
		saveFile << playerFuel << endl;
		saveFile << stamina << endl;
		saveFile << enemySpeed << endl;
		saveFile << score << endl;
		saveFile << fuelDepotSpawnDelay << endl;
		saveFile << bulletCooldown << endl;
		saveFile << currentBulletCooldown << endl;
		saveFile << fuelDepots.size() << endl;
		for (const auto& depot : fuelDepots)
		{
			saveFile << depot->getX() << " " << depot->getY();
		}
		saveFile << backgrounds.size() << endl;
		for (const auto& bg : backgrounds)
		{
			saveFile << bg->getX() << " " << bg->getY() << " " << bg->getWidth() << " " << bg->getHeight() << endl;
		}
		saveFile << bullets.size() << endl;
		for (const auto& bullet : bullets)
		{
			saveFile << bullet->getX() << " " << bullet->getY();
		}
		saveFile << enemySpawnDelay << endl;
		saveFile << backgroundSpeed << endl;
		saveFile << shapes.size() << endl;
		for (const auto& enemy : shapes)
		{
			saveFile << enemy->getX() << " " << enemy->getY() << " " << enemy->getWidth() << " " << enemy->getHeight() << endl;
		}

		// Display a "Saving..." message
		const string SaveText = "Saving........";
		int textWidth, textHeight;

		window* pWind = getWind();
		if (pWind) {
			pWind->SetFont(30, BOLD, SWISS);
			pWind->GetStringSize(textWidth, textHeight, SaveText);

			// Calculate the bottom left position for the text
			int X = textWidth;
			int Y = (pWind->GetHeight() - textHeight);
			//Display message
			for (int alpha = 0; alpha <= 255; alpha += 15) {
				pWind->SetPen(YELLOW);
				pWind->DrawString(X, Y, SaveText);
				//pWind->UpdateBuffer();
				Pause(20); // Pause for the fade-in effect
			}
		}
		saveFile.close();
	}
	else
	{
		cout << "Unable to open file for saving." << endl;
	}
}
void Game::loadGame()
{
    ifstream loadFile("save.txt");
    if (loadFile.is_open())
    {
        int planeY;
        loadFile >> planeY;
        gamePlane->setY(planeY);
        
        loadFile >> playerLives;
        loadFile >> playerFuel;
        loadFile >> stamina;
        loadFile >> enemySpeed;
        loadFile >> score;
        loadFile >> fuelDepotSpawnDelay;
        loadFile >> bulletCooldown;
        loadFile >> currentBulletCooldown;
        for (auto* depot : fuelDepots) delete depot;
        fuelDepots.clear();
        
        for (auto* bg : backgrounds) delete bg;
        backgrounds.clear();
        
        for (auto* bullet : bullets) delete bullet;
        bullets.clear();
        
        for (auto* enemy : shapes) delete enemy;
        shapes.clear();
        int numDepots;
        loadFile >> numDepots;
        for (int i = 0; i < numDepots; i++)
        {
            int x, y, width, height;
            loadFile >> x >> y >> width >> height;
            FuelDepot* depot = new FuelDepot(this, {x, y}, width, height, BLACK, YELLOW);
            fuelDepots.push_back(depot);
        }

        // Load backgrounds
        int numBackgrounds;
        loadFile >> numBackgrounds;
        for (int i = 0; i < numBackgrounds; i++)
        {
            int x, y, width, height;
            loadFile >> x >> y >> width >> height;
            // Since we can't determine the exact type, we'll create Trees as default
            Background* bg = new Tree(this, {x, y}, width, height, GREEN ,BROWN, GREEN);
            backgrounds.push_back(bg);
        }

        // Load bullets
        int numBullets;
        loadFile >> numBullets;
        for (int i = 0; i < numBullets; i++)
        {
            int x, y, width, height;
            loadFile >> x >> y >> width >> height;
            Bullet* bullet = new Bullet(this, {x, y}, width, height, RED, RED);
            bullets.push_back(bullet);
        }

        loadFile >> enemySpawnDelay;
        loadFile >> backgroundSpeed;

        // Load enemies
        int numEnemies;
        loadFile >> numEnemies;
        for (int i = 0; i < numEnemies; i++)
        {
            int x, y, width, height;
            loadFile >> x >> y >> width >> height;
            // Since we can't determine the exact type, we'll create Jets as default
            Enemy* enemy = new Jet(this, {x, y}, width, height, BLACK, BLACK, BLACK, BLACK);
            shapes.push_back(enemy);
        }

        // Display a "Loading..." message
        const string LoadText = "Loading........";
        int textWidth, textHeight;

        window* pWind = getWind();
        if (pWind) {
            pWind->SetFont(30, BOLD, SWISS);
            pWind->GetStringSize(textWidth, textHeight, LoadText);

            // Calculate the bottom left position for the text
            int X = textWidth;
            int Y = (pWind->GetHeight() - textHeight);
            
            // Display message
            for (int alpha = 0; alpha <= 255; alpha += 15) {
                pWind->SetPen(GREEN);
                pWind->DrawString(X, Y, LoadText);
                Pause(20); // Pause for the fade-in effect
            }
        }

        loadFile.close();
    }
    else
    {
        cout << "Unable to open file for loading." << endl;
    }
}
void Game::togglePause() {
	isPaused = !isPaused;
	
	if (isPaused) {
		// Draw pause screen
		const string pauseText = "GAME PAUSED";
		const string resumeText = "Press ESC to Resume";
		int textWidth, textHeight;

		if (pWind) {
			// Dark overlay (using dark gray instead of semi-transparent black)
			pWind->SetPen(DARKGRAY, 1);
			pWind->SetBrush(DARKGRAY);
			pWind->DrawRectangle(0, 0, config.windowWidth, config.windowHeight, FILLED);

			// Draw pause text
			pWind->SetFont(50, BOLD, SWISS);
			pWind->GetStringSize(textWidth, textHeight, pauseText);
			int centerX = (config.windowWidth - textWidth) / 2;
			int centerY = (config.windowHeight - textHeight) / 2;
			
			pWind->SetPen(WHITE);
			pWind->DrawString(centerX, centerY, pauseText);

			// Draw resume instruction
			pWind->SetFont(20, PLAIN, SWISS);
			pWind->GetStringSize(textWidth, textHeight, resumeText);
			centerX = (config.windowWidth - textWidth) / 2;
			pWind->DrawString(centerX, centerY + 60, resumeText);
			
			pWind->UpdateBuffer();
		}
	}
}

void Game::PlaySound()
{
	static time_t lastSpawnTime = time(0);
	time_t now = time(0);

	// Play sound every 83 seconds (83000 ms)
	double spawnDelay = 83; // seconds

	if (difftime(now, lastSpawnTime) >= spawnDelay)
	{
		// Call the Windows API PlaySound, not this method
		::PlaySound(TEXT("Super Mario Bros. Theme Song - ultragamemusic(1).wav"), NULL, SND_FILENAME | SND_ASYNC);
		lastSpawnTime = now;
	}
}


void Game::go() 
{
	::PlaySound(TEXT("Super Mario Bros. Theme Song - ultragamemusic(1).wav"), NULL, SND_FILENAME | SND_ASYNC);
	while(true)
	{
		while (playerLives > 0) {
			// Handle pause/resume with escape key
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
				if (!escapePressed) {
					togglePause();
					escapePressed = true;
				}
			} else {
				escapePressed = false;
			}

			// Skip update if game is paused
			if (!isPaused) {
				ClearWindow();
				drawBackground();
				MoveBackground();
				GenerateRandomEnemies();
				SpawnFuelDepots();
				UpdateFuelDepots();
				PlaySound();
				gamePlane->move();
				gamePlane->draw();
				Update();
				Draw();
				if (GetAsyncKeyState('S') & 0x8000 && GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
					saveGame();
				}
				if (GetAsyncKeyState('L') & 0x8000 && GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
					loadGame();
				}
			}
			
			pWind->UpdateBuffer();
			Pause(20);
		}
		GameOver();
	}
}

