#pragma once

#include "Drawable.hpp"
#include "Effect.hpp"
#include "rng.hpp"
#include "spriteSheet.hpp"
#include <SFML/Graphics.hpp>

template <typename DrawPolicy>
class _TurretFlashEffect
    : public Drawable<_TurretFlashEffect<DrawPolicy>, DrawPolicy>,
      public Effect {
public:
    static const int drawOffset = 11;
    _TurretFlashEffect(const sf::Texture & txtr, float x, float y)
        : Effect(x, y) {
        spriteSheet.setTexture(txtr);
        bool select = rng::random<2>();
        if (select) {
            spriteSheet.setScale(-1.f, 1.f);
            position.x += 17;
        }
        spriteSheet.setPosition(position.x, position.y);
    }
    template <typename Game> void update(const sf::Time & elapsedTime, Game *) {
        timer += elapsedTime.asMilliseconds();
        if (timer > 40) {
            timer -= 40;
            frameIndex += 1;
            if (frameIndex > 4) {
                setKillFlag();
                frameIndex = 4;
            };
        }
    }
    const sf::Sprite & getSprite() const { return spriteSheet[frameIndex]; }

private:
    mutable SpriteSheet<0, 116, 16, 16> spriteSheet;
};
