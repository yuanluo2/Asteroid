#pragma once

#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Bullet.hpp"
#include "Config.hpp"

namespace asteroid {
	class BulletGen {
		sf::Texture texture;
	public:
		BulletGen():
			texture{}
		{
			if (!texture.loadFromFile(asteroid::config::PIC_BULLET)) {
				std::cerr << "can't load file: " << asteroid::config::PIC_BULLET << "\n";
				std::exit(EXIT_FAILURE);
			}
		}

		Bullet operator()(const sf::Vector2f& position) {
			return Bullet{ texture, position };
		}
	};
};
