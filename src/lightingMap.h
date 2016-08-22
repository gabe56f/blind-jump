//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <vector>
#include "coordinate.hpp"
#include <cmath>

#define CIRC_RADIUS 200

typedef struct __circle {
	int x;
	int y;
	int r;
} Circle;

bool checkOverlap(Circle c1, Circle c2) {
	double centerDifference = sqrt((double) (32 * (c1.x - c2.x)) * (32 * (c1.x - c2.x)) + (26 * (c1.y - c2.y)) * (26 * (c1.y - c2.y)));
	if (centerDifference <= (double) c1.r || centerDifference <= (double) c2.r) {
		return true;
	}
	return false;
}

void getLightingPositions(uint8_t gameMap[61][61], std::vector<Coordinate>& availableLocations, Circle & teleporterFootprint) {
	// First create a temporary map containing only the surfaces from the game map
	std::vector<Circle> lightMap;
	int i, j;
	for (i = 0; i < 61; i++) {
		for (j = 0; j < 61; j++) {
			Circle c;
			if (gameMap[i][j] == 3 || gameMap[i][j] == 4 || gameMap[i][j] == 8 || gameMap[i][j] == 11) {
				c.x = i;
				c.y = j;
				c.r = CIRC_RADIUS + std::abs(static_cast<int>(global::RNG())) % 40;
				lightMap.push_back(c);
			}
		}
	}

	for (std::vector<Circle>::iterator it = lightMap.begin(); it != lightMap.end();) {
		if (checkOverlap(teleporterFootprint, *it)) {
			it = lightMap.erase(it);
		} else {
			++it;
		}
	}
	
	size_t length = lightMap.size();
	// Randomly shuffle the vector so not to just pick elements that are spatially close
	std::random_shuffle(lightMap.begin(), lightMap.end());
	for (size_t i = 0; i < length; i++) {
		// Remove all intersecting circles
		for (std::vector<Circle>::iterator it = lightMap.begin(); it != lightMap.end();) {
			if (checkOverlap(lightMap[i], *it) && (it->x != lightMap[i].x || it->y != lightMap[i].y)) {
				it = lightMap.erase(it);
				length--;
			} else {
				++it;
			}
		}
	}
	
	// Now add whatever's left to the vector of available coordinates
	for (auto element : lightMap) {
		Coordinate c;
		c.x = element.x;
		c.y = element.y;
		availableLocations.push_back(c);
	}
}
