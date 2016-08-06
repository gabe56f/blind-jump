//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
//                                                                        //
// This program is free software: you can redistribute it and/or modify   //
// it under the terms of the GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or      //
// (at your option) any later version.                                    //
//                                                                        //
// This program is distributed in the hope that it will be useful,        //
// but WITHOUT ANY WARRANTY; without even the implied warranty of         //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
// GNU General Public License for more details.                           //
//                                                                        //
// You should have received a copy of the GNU General Public License      //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.  //
//========================================================================//

#pragma once
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "player.hpp"

class Camera {
	Player * pTarget;
	sf::View view;
	float movementRate;
	float xPos, yPos;

public:
	Camera(Player * _pTarget, const sf::Vector2f & viewPort) :
		pTarget{nullptr},
		view{sf::Vector2f(viewPort.x / 2, viewPort.y / 2), viewPort},
		movementRate{0.f},
		xPos{0.f},
		yPos{0.f}
	{}
	void update(const sf::Time &);
	const sf::View & getView() const;
};
