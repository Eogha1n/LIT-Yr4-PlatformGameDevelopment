/*
	Level3.cpp

	Joe O'Regan
	K00203642
	18/02/2018

	Added additional level 3 with differnt enemies and spawn times
*/
#include "Level.h"
#include "Level3.h"
#include "Input.h"
#include "EnemyShipKling.h"
#include "EnemyShipWilKnot.h"

Scene* Level3::createScene() {
	cocos2d::Scene* scene = Scene::create();				// 'scene' is an autorelease object, JOR replaced auto specifier   
	s_pLayerInstance = Level3::create();					// 'layer' is an autorelease object, JOR replaced auto specifier  
	//layer->setName("Level3");								// Set name for layer to access (//Director::getInstance()->getRunningScene()->getChildByName("Level1")->addChild();)
	scene->addChild(s_pLayerInstance);						// Add layer as a child to scene	    
	return scene;											// Return the scene
}

/*
	Initialisation specific to Level 3
*/
bool Level3::init() {
	Level::init();																		// 20180221 Added Level base class

	Game::Instance()->setLevel(3);														// Specific to level 2
	m_pHUD->setLevelLabel();															// Update HUD Level text display

	if (!Layer::init()) { return false; }												// super init first

	CCLOG("Clear enemy ship vector");

	//initEnemyShips();																	// Add the new enemy with double lasers to the list of enemies

	Game::Instance()->resetAsteroidKills();												// Reset the number of asteroids destroyed
	Game::Instance()->resetEnemyShipKIlls();											// Reset the number of enemy ships destroyed
	
	// ParallaxNode
	this->addChild(m_backgroundNode, -1);												// Add the parallax background
	m_backgroundNode->init();															// Initialise the parallax scrolling background

	m_enemyLaserList3 = new Vector<Sprite*>(NUM_LASERS);								// List of lasers
	for (int i = 0; i < NUM_LASERS; ++i) {
		cocos2d::Sprite* enemyLaser = Sprite::create(LASER_GREEN_IMG);					// Laser sprite, JOR replaced auto specifier
		enemyLaser->setVisible(false);
		this->addChild(enemyLaser);
		m_enemyLaserList3->pushBack(enemyLaser);
	}
	
	this->scheduleUpdate();																// Start updating the scene

	return true;
}

/*
	Initialise the level 3 ships, adding to the list of enemies
*/
void Level3::initEnemyShips() {
	// Made function virtual not need to clear list now, as function in level not loaded

	//m_enemyLaserList->clear();														// No need to clear, now a virtual function used
	//for (int i = 0; i <= m_enemyShipList->size()+1; ++i) {
	//	m_enemyShipList->popBack();
	//	CCLOG("Remove Enemy ship %d / %d from list", i, m_enemyShipList->size());
	//}

	// Add 2 x Enemy Ship Type 2 - These will appear first on screen
	for (unsigned int i = 0; i < L3_NUM_ENEMY_2; ++i) {
		EnemyShip* enemyShip2 = EnemyShipKling::create(m_visibleSize);					// Add 3 Type 2 enemies, spawns 1st
		this->addChild(enemyShip2);
		m_enemyShipList->pushBack(enemyShip2);
	}

	// Add 1 x Enemy Ship Type 1 - This will appear second
	for (unsigned int i = 0; i < L3_NUM_ENEMY_1; ++i) {
		EnemyShip* enemyShip1 = EnemyShip::create(m_visibleSize);						// Add Type 1 enemies, spawns 2nd
		this->addChild(enemyShip1);
		m_enemyShipList->pushBack(enemyShip1);
	}

	// Add 3 x Enemy Ship Type 3 - Third on screen
	for (unsigned int i = 0; i < L3_NUM_ENEMY_3; ++i) {
		EnemyShip* enemyShip3 = EnemyShipWilKnot::create(m_visibleSize);				// Add type 3 enemies spawning 3rd in the cycle
		this->addChild(enemyShip3);
		m_enemyShipList->pushBack(enemyShip3);
	}

	// Add 2 x Enemy Ship Type 1 - 4th
	for (unsigned int i = 0; i < L3_NUM_ENEMY_1+1; ++i) {
		EnemyShip* enemyShip1 = EnemyShip::create(m_visibleSize);						// Add 2 more type 1 enemies
		this->addChild(enemyShip1);
		m_enemyShipList->pushBack(enemyShip1);
	}

	CCLOG("Add enemy ships");
}

/*
	Update level 3
*/
void Level3::update(float dt) {
	Level::update(dt);																	// Call base class update function		
}

/*
	check collisions with level 3 enemies and lasers NOT FULLY IMPLEMENTED FOR ENEMY LASERS ...YET
*/
void Level3::checkCollisions() {
	Level::checkCollisions();															// Call base class function

	// Check collisions with different objects in different levels
	
	// Check collisions laser type 2 (Orange)
	for (cocos2d::Sprite* enemyLaser : *m_enemyLaserList2) {
		if (!(enemyLaser->isVisible())) continue;

		if (enemyLaser->getPosition().x <= 0)											// If the laser moves off screen it's own width
			enemyLaser->setVisible(false);												// Hide the laser

		// Check collisions between the player ship and Laser type 2 (Orange)
		if (player->getBoundingBox().intersectsRect(enemyLaser->getBoundingBox())) {	// If the ship collides with an asteroid
			enemyLaser->setVisible(false);												// Destroy the asteroid
			player->damage();
		}
	}

	// Check collisions for laser type 3 (Green)
	for (cocos2d::Sprite* enemyLaser : *m_enemyLaserList3) {
		if (!(enemyLaser->isVisible())) continue;

		if (enemyLaser->getPosition().x <= 0)											// If the laser moves off screen it's own width
			enemyLaser->setVisible(false);												// Hide the laser

		// Check collisions between the player ship and Laser type 3 (Green)
		if (player->getBoundingBox().intersectsRect(enemyLaser->getBoundingBox())) {	// If the ship collides with an asteroid
			enemyLaser->setVisible(false);												// Destroy the asteroid
			player->damage();
		}
	}
}

/*
	End scene, nothing different needed
*/
void Level3::endScene(EndReason endReason) {	
	Level::endScene(endReason);															// End the scene
}
