#pragma once

#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Config.hpp"

namespace asteroid {
	class Asteroid {
		sf::Sprite sprite;
		float scaleFactor;
		int hitsNum;
	public:
		Asteroid(sf::Texture& texture, float xPos, float _scaleFactor) :
			sprite{},
			scaleFactor{ _scaleFactor },
			hitsNum{ 0 }
		{
			sprite.setTexture(texture);
			sprite.setScale(scaleFactor, scaleFactor);
			sprite.setPosition(xPos, 0);
		}

		void draw(sf::RenderTarget& rt) {
			rt.draw(sprite);
		}

		void increaseHits() {
			++hitsNum;
		}

		void markDestroy() {
			hitsNum = 3;
		}

		bool needDestroy() const {
			using namespace asteroid::config;

			if (scaleFactor >= SCALE_FACTOR_MIDDLE_UPPER_BOUND && scaleFactor < SCALE_FACTOR_UPPER_BOUND) {
				return hitsNum >= 3;
			}
			else if (scaleFactor >= SCALE_FACTOR_MIDDLE_LOWER_BOUND && scaleFactor < SCALE_FACTOR_MIDDLE_UPPER_BOUND) {
				return hitsNum >= 2;
			}
			else {
				return hitsNum >= 1;
			}
		}

		sf::FloatRect getGlobalBounds() const {
			return sprite.getGlobalBounds();
		}

		void update() {
			// asteroid always goes down.
			sprite.move(0, asteroid::config::ASTEROID_SPEED);
		}
	};
};
