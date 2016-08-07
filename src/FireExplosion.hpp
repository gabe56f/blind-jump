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

#include "SFML/Graphics.hpp"
#include "spriteSheet.hpp"
#include "Effect.hpp"
#include "easingTemplates.hpp"

class FireExplosion : public Effect {
private:
	mutable SpriteSheet<208, 173, 58, 51> spriteSheet;
	sf::Sprite glow;
    int64_t glowFadeTimer;
	
public:
	FireExplosion(const sf::Texture &, const sf::Texture &, float, float);
	void update(const sf::Time &);
	const sf::Sprite & getSprite() const;
	const sf::Sprite & getGlow() const;
};
