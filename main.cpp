#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Background.hpp"
#include "Ship.hpp"
#include "Asteroid.hpp"
#include "AsteroidGen.hpp"
#include "Bullet.hpp"
#include "BulletGen.hpp"
#include "Config.hpp"

// When you use visual studio to compile this project, use the following command to hide the cmd.
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

using namespace asteroid::config;
using namespace std::string_literals;

class Game {
	sf::RenderWindow window;
	asteroid::Background background;
	asteroid::Ship ship;
	asteroid::BulletGen bulletGen;
	asteroid::AsteroidGen asteroidGen;
	std::vector<asteroid::Asteroid> asteroids;
	std::vector<asteroid::Bullet> bullets;
	bool paused;

	void processEvents() {
		sf::Event event {};

		while (window.pollEvent(event) || paused) {
			switch (event.type) {
			case sf::Event::LostFocus:
				paused = true;   // pause game.
				break;
			case sf::Event::Closed:
				std::exit(EXIT_SUCCESS);
			case sf::Event::KeyPressed:
				if (paused) {
					paused = false;
					continue;
				}

				// press esc will also pause game.
				if (event.key.code == sf::Keyboard::Escape) {
					paused = true;
				}
			}
		}
	}

	// if a bullet collides with an asteroid, mark them to remove.
	void markBulletsAndAsteroids() {
		for (auto& bullet: bullets) {
			for (auto& asteroid : asteroids) {
				if (bullet.getGlobalBounds().intersects(asteroid.getGlobalBounds())) {
					bullet.markDestroy();
					asteroid.increaseHits();
				}
			}
		}
	}

	// if an asteroid collides with our ship, mark it to remove.
	void markShipAndAsteroids() {
		sf::FloatRect shipRect = ship.getGlobalBounds();

		for (auto& asteroid : asteroids) {
			if (shipRect.intersects(asteroid.getGlobalBounds())) {
				asteroid.markDestroy();
			}
		}
	}

	// when a bullet goes out of the window, mark it to remove.
	void markBulletsOutOfWindow() {
		for (auto& bullet : bullets) {
			auto rect = bullet.getGlobalBounds();

			if (rect.top + rect.height <= 0) {
				bullet.markDestroy();
			}
		}
	}

	// when an asteroid goes out of the window, mark it to remove.
	void markAsteroidsOutOfWindow() {
		for (auto& asteroid : asteroids) {
			auto rect = asteroid.getGlobalBounds();

			if (rect.top >= asteroid::config::WINDOW_HEIGHT) {
				asteroid.markDestroy();
			}
		}
	}

	void update() {
		markBulletsAndAsteroids();
		markShipAndAsteroids();
		markBulletsOutOfWindow();
		markAsteroidsOutOfWindow();

		// erase the marked bullets and asteroids.
		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](asteroid::Bullet& elem) { return elem.needDestroy(); }), bullets.end());
		asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(), [](asteroid::Asteroid& elem) { return elem.needDestroy(); }), asteroids.end());

		// update our ship's position.
		ship.update();

		// update each bullets and asteroids.
		std::for_each(bullets.begin(), bullets.end(), [](asteroid::Bullet& elem) { elem.update(); });
		std::for_each(asteroids.begin(), asteroids.end(), [](asteroid::Asteroid& elem) { elem.update(); });
	}

	void render() {
		window.clear();

		// draw things here.
		background.draw(window);
		ship.draw(window);
		std::for_each(asteroids.begin(), asteroids.end(), [this](asteroid::Asteroid& elem) { elem.draw(window); });
		std::for_each(bullets.begin(), bullets.end(), [this](asteroid::Bullet& elem) { elem.draw(window); });

		window.display();
	}
public:
	Game():
		window{ sf::VideoMode{ WINDOW_WIDTH, WINDOW_HEIGHT }, "Asteroid"s },
		asteroidGen{},
		bulletGen{},
		background{},
		ship{},
		paused{ false }
	{	
		window.setFramerateLimit(asteroid::config::FRAME_RATE);
	}

	void play() {
		uint8_t bulletCounter = 0;
		uint8_t asteroidCounter = 0;

		while (window.isOpen()) {
			processEvents();
			update();
			render();

			++bulletCounter;
			++asteroidCounter;

			if (bulletCounter == 20) {
				auto rect = ship.getGlobalBounds();
				bullets.emplace_back(bulletGen(sf::Vector2f{ rect.left + rect.width / 2, rect.top }));
				bulletCounter = 0;
			}

			if (asteroidCounter == 15) {
				asteroids.emplace_back(asteroidGen());
				asteroidCounter = 0;
			}
		}
	}
};

int main() {
	Game game;
	game.play();
}
