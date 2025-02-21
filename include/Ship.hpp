#pragma once

#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Config.hpp"

namespace asteroid {
	class Ship {
		sf::Texture texture;
		sf::Sprite sprite;
	public:
		Ship() :
			texture{},
			sprite{}
		{
			using namespace asteroid::config;

			if (!texture.loadFromFile(PIC_SHIP)) {
				std::cerr << "can't load file: " << PIC_SHIP << "\n";
				std::exit(EXIT_FAILURE);
			}

			sprite.setTexture(texture);

			// set the origin to the center.
			sf::Vector2u textureSize = texture.getSize();
			sf::Vector2f textureVec{ static_cast<float>(textureSize.x), static_cast<float>(textureSize.y) };
			sprite.setOrigin(textureVec / 2.0f);

			// picture is too big, make it appear smaller.
			sprite.setScale(0.1f, 0.1f);

			// set the position to the center.
			sf::FloatRect rect = sprite.getGlobalBounds();
			sf::Vector2f posRect{ static_cast<float>(WINDOW_WIDTH) / 2.0f, static_cast<float>(WINDOW_HEIGHT) - rect.height / 2.0f };
			sprite.setPosition(posRect);
		}

		const sf::Vector2f& getPosition() const {
			return sprite.getPosition();
		}

		void draw(sf::RenderTarget& rt) {
			rt.draw(sprite);
		}

		sf::FloatRect getGlobalBounds() const {
			return sprite.getGlobalBounds();
		}

		void update() {
			using namespace asteroid::config;

			sf::FloatRect rect = sprite.getGlobalBounds();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				if (rect.top - SHIP_SPEED >= 0) {
					sprite.move(0, -SHIP_SPEED);
				}
			}

			rect = sprite.getGlobalBounds();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				if (rect.top + rect.height + SHIP_SPEED <= WINDOW_HEIGHT) {
					sprite.move(0, SHIP_SPEED);
				}
			}

			rect = sprite.getGlobalBounds();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				if (rect.left - SHIP_SPEED >= 0) {
					sprite.move(-SHIP_SPEED, 0);
				}
			}

			rect = sprite.getGlobalBounds();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				if (rect.left + rect.width + SHIP_SPEED <= WINDOW_WIDTH) {
					sprite.move(SHIP_SPEED, 0);
				}
			}
		}
	};
};
