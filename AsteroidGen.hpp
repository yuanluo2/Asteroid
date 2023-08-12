#pragma once

#include <iostream>
#include <random>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Asteroid.hpp"
#include "Config.hpp"

namespace asteroid {
	class AsteroidGen {
		std::random_device rd;
		std::mt19937 mt;
		std::uniform_real_distribution<float> scaleDist;
		std::uniform_real_distribution<float> xPosDist;
		sf::Texture texture;
	public:
		AsteroidGen() :
			texture{},
			rd{},
			mt{ rd() },      // be careful here, not just rd
			scaleDist{ asteroid::config::SCALE_FACTOR_LOWER_BOUND, asteroid::config::SCALE_FACTOR_UPPER_BOUND },
			xPosDist{ 0.0f, static_cast<float>(asteroid::config::WINDOW_WIDTH) }
		{
			if (!texture.loadFromFile(asteroid::config::PIC_ASTEROID)) {
				std::cerr << "can't load file: " << asteroid::config::PIC_ASTEROID << "\n";
				std::exit(EXIT_FAILURE);
			}
		}

		Asteroid operator()() {
			auto scaleFactor = scaleDist(mt);
			auto xPos = xPosDist(mt);
			return Asteroid{ texture, xPos, scaleFactor };
		}
	};
};
