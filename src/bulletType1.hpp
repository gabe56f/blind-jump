//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "Effect.hpp"
#include "spriteSheet.hpp"
#include <SFML/Graphics.hpp>

class PlayerShot : public Effect {
public:
    using HBox = framework::HitBox<12, 12, 2, 2>;
    PlayerShot(const sf::Texture &, const sf::Texture &, char, float, float);
    const sf::Sprite & getSprite();
    const sf::Sprite & getGlow();
    void update(const sf::Time &);
    char getDirection();
    bool checkCanPoof();
    void poof();
    void disablePuff();
    const HBox & getHitBox() const;

private:
    float xInit, yInit;
    HBox hitBox;
    SpriteSheet<44, 75, 16, 16> spriteSheet; // This could easily be a plain
                                             // sprite, but the memory usage
                                             // would be the same
    SpriteSheet<88, 145, 16, 16> puffSheet;
    sf::Sprite glow;
    char direction;
    bool canPoof;
    enum class State { travelling, poof };
    State state;
};
