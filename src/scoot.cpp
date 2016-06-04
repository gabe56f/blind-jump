//
//  scoot.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/21/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "scoot.hpp"
#include <cmath>
#include "angleFunction.hpp"

#define PI 3.14159265

//// EASY LOW LEVEL ENEMY

Scoot::Scoot(sf::Sprite* inpSpr) : EnemyParent(inpSpr) {
	// Store all of the input sprites
	for (auto i = 0; i < 3; i++) {
		sprites[i] = inpSpr[i];
		sprites[i].setOrigin(6, 6);
	}
	frameTimer = 10 + rand() % 30;
	frameIndex = rand() % 2;
	// Start the enemy moving in a random direction
	float dir = rand() % 359;
	hSpeed = cos(dir) * 0.5;
	vSpeed = sin(dir) * 0.5;
	// Offset each enemy object so they don't all do the same thing at once
	unsigned char offset = (unsigned char) rand() % 240;
	changeDirTimer = offset;
	shotCountdownTimer = 80 + offset;
	health = 2;
	speedScale = 1.f;
}

void Scoot::randDir() {
	float dir = rand() % 359;
	hSpeed = cos(dir) * 0.5;
	vSpeed = sin(dir) * 0.5;
}

void Scoot::checkBulletCollision(effectsController& ef) {
	//Check collisions with player's shots, but only if the shot vectors aren't empty
	if (!ef.getBulletLayer1().empty()) {
		for (auto & element : ef.getBulletLayer1()) {
			if (std::abs(element.getXpos() - (xPos - 6)) < 6 && std::abs(element.getYpos() - (yPos - 6)) < 6 && !isColored) {
				element.setKillFlag();		   // Kill the bullet if there's a collision between the bullet and the enemy
				// Tons of effects in one place is distracting, so don't draw another one if the enemy is about to explode
				if (health == 1) {
					element.disablePuff();
				}
				health -= 1;
				isColored = true;
				colorAmount = 1.f;
			}
		}
	}
	if (!ef.getBulletLayer2().empty()) {
		for (auto & element : ef.getBulletLayer2()) {
			if (std::abs(element.getXpos() - (xPos - 6)) < 6 && std::abs(element.getYpos() - (yPos - 6)) < 6 && !isColored) {
				element.setKillFlag();
				if (health == 1) {
					element.disablePuff();
				}
				health -= 1;
				isColored = true;
				colorAmount = 1.f;
			}
		}
	}
	
	if (health == 0) {
		killFlag = 1;
		unsigned long int temp = rand() % 5;
		if (temp == 0) {
			ef.addHearts(xInit, yInit);
		} else {
			ef.addCoins(xInit, yInit);
		}
		ef.addFireExplosion(xInit, yInit - 2);
	}
}

void Scoot::update(float xOffset, float yOffset, std::vector<wall> w, effectsController & ef, sf::Time & elapsedTime) {
	// Update the enemy's position
	setPosition(xOffset, yOffset);
	checkBulletCollision(ef);
	if (isColored) {
		colorTimer += elapsedTime.asMilliseconds();
		if (colorTimer > 20.f) {
			colorTimer -= 20.f;
			colorAmount -= 0.1f;
		}
		
		if (colorAmount <= 0.f) {
			isColored = false;
		}
	}
	for (auto i = 0; i < 2; i++) {
		sprites[i].setPosition(xPos, yPos);
	}
	sprites[2].setPosition(xPos, yPos + 10);
	// Check for collisions with walls, with a certain radius constraint
	bool foundCollision = checkCollisionWall(w, 48);
	// Redirect the enemy if a collision occurs with a wall
	if (foundCollision) {
		hSpeed *= -1;
		vSpeed *= -1;
	}
	
	// Flip the sprite to face the player
	if (xPos > playerPosX) {
		sf::Vector2f scaleVec(1, 1);
		sprites[0].setScale(scaleVec);
		sprites[1].setScale(scaleVec);
	}
	else {
		sf::Vector2f scaleVec(-1, 1);
		sprites[0].setScale(scaleVec);
		sprites[1].setScale(scaleVec);
	}
	xInit += (elapsedTime.asMilliseconds() / 17.6) * hSpeed * speedScale;
	yInit += (elapsedTime.asMilliseconds() / 17.6) * vSpeed * speedScale;
	
	changeDirTimer += elapsedTime.asMilliseconds();
	shotCountdownTimer += elapsedTime.asMilliseconds();
	frameTimer += elapsedTime.asMilliseconds();
	
	if (changeDirTimer > 1400) {
		changeDirTimer -= 1408;
		if (rand() % 2) {
			float dir = rand() % 359;
			hSpeed = cos(dir) * 0.5;
			vSpeed = sin(dir) * 0.5;
		}
		else {
			float dir = atan((yPos - playerPosY) / (xPos - playerPosX));
			hSpeed = cos(dir) * 0.5;
			vSpeed = sin(dir) * 0.5;
			// To correct for negative sine and cosine function outputs
			if (xPos > playerPosX) {
				hSpeed *= -1;
				vSpeed *= -1;
			}
		}
	}
	if (shotCountdownTimer > 420) {
		speedScale = 0.5;
	}
	
	if (shotCountdownTimer > 4224) {
		shotCountdownTimer -= 4224;
		// Push back away from the player and shoot some lasers
		ef.addTurretFlash(xInit - 8, yInit - 12);
		ef.addScootShot(xInit - 8, yInit - 12, angleFunction(xPos -8, yPos - 8, playerPosX, playerPosY), playerPosX, playerPosY);
		ef.addScootShot(xInit - 8, yInit - 12, angleFunction(xPos -8, yPos - 8, playerPosX, playerPosY) + 28, playerPosX, playerPosY);
		ef.addScootShot(xInit - 8, yInit - 12, angleFunction(xPos -8, yPos - 8, playerPosX, playerPosY) - 28, playerPosX, playerPosY);
		float dir = atan((yPos - playerPosY) / (xPos - playerPosX));
		speedScale = 3.0;
		hSpeed = -cos(dir);
		vSpeed = -sin(dir);
		// To correct for negative sine and cosine function outputs
		if (xPos > playerPosX) {
			hSpeed *= -1;
			vSpeed *= -1;
		}
	}
}

void Scoot::softUpdate(float xOffset, float yOffset) {
	// Update the enemy's position
	setPosition(xOffset, yOffset);
	for (auto i = 0; i < 2; i++) {
		sprites[i].setPosition(xPos, yPos);
	}
}

sf::Sprite* Scoot::getSprite() {
	// Step through the frames of the animation
	if (frameTimer > 87) {
		frameTimer -= 87;
		if (frameIndex == 0) {
			frameIndex = 1;
		}
		else {
			frameIndex = 0;
		}
	}
	return &sprites[frameIndex];
}

sf::Sprite* Scoot::getShadow() {
	return &sprites[2];
}

bool Scoot::colored() {
	return isColored;
}