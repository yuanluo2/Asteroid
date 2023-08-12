#pragma once

namespace asteroid {
	namespace config {
		constexpr const char* PIC_SHIP          = R"(resources\ship.png)";
		constexpr const char* PIC_BULLET        = R"(resources\bullet.png)";
		constexpr const char* PIC_BACKGROUND    = R"(resources\background.jpg)";
		constexpr const char* PIC_ASTEROID      = R"(resources\asteroid.png)";

		constexpr unsigned int WINDOW_WIDTH = 1440;
		constexpr unsigned int WINDOW_HEIGHT = 900;
		constexpr const char*  WINDOW_TITLE = "Asteroid";

		constexpr unsigned int FRAME_RATE = 60;

		constexpr float SHIP_SPEED   = 10.0f;
		constexpr float BULLET_SPEED = 10.0f;
		constexpr float ASTEROID_SPEED = 10.0f;

		constexpr float SCALE_FACTOR_LOWER_BOUND = 0.1f;
		constexpr float SCALE_FACTOR_MIDDLE_LOWER_BOUND = 0.17f;
		constexpr float SCALE_FACTOR_MIDDLE_UPPER_BOUND = 0.24f;
		constexpr float SCALE_FACTOR_UPPER_BOUND = 0.3f;
	};
};
