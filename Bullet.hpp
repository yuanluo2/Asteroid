#pragma once

#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Config.hpp"

namespace asteroid {
	class Bullet {
		sf::Sprite sprite;
		bool destroyMark;
	public:
		Bullet(sf::Texture& texture, const sf::Vector2f& position) :
			sprite{},
			destroyMark{ false }
		{
			sprite.setTexture(texture);
			sprite.setPosition(position);
		}

		void draw(sf::RenderTarget& rt) {
			rt.draw(sprite);
		}

		void markDestroy() {
			destroyMark = true;
		}

		bool needDestroy() const {
			return destroyMark;
		}

		sf::FloatRect getGlobalBounds() const {
			return sprite.getGlobalBounds();
		}

		void update() {
			// bullet always goes up.
			sprite.move(0, -1.0f * asteroid::config::BULLET_SPEED);
		}
	};
};
