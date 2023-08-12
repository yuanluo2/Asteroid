#pragma once

#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Config.hpp"

namespace asteroid {
	class Background {
		sf::Texture texture;
		sf::Sprite sprite;
	public:
		Background() :
			texture{},
			sprite{}
		{
			using namespace asteroid::config;

			if (!texture.loadFromFile(PIC_BACKGROUND)) {
				std::cerr << "can't load file: " << PIC_BACKGROUND << "\n";
				std::exit(EXIT_FAILURE);
			}

			sprite.setTexture(texture);
		}

		void draw(sf::RenderTarget& rt) {
			rt.draw(sprite);
		}
	};
};
