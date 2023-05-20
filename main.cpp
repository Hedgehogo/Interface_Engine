#include "lib/ui/UI.hpp"
#include <iostream>
#include <array>

template<typename I, I T>
float calculateMediumFPS(std::array<float, T> lastFPS) {
	float sum = 0.0f;
	for(const auto& fps: lastFPS) {
		sum += fps;
	}
	return sum / static_cast<float>(lastFPS.size());
}

int main(int argc, char *argv[]) {
	ui::init();
	
	ui::Window window(
		"../example-resources/test.yaml",
		"IE works!",
		{200, 100},
		sf::ContextSettings{
			0, 0, 1
		}
	);
	
	sf::Clock clock;
	std::array<float, 500> lastFPS{};
	
	while(window.isOpen()) {
		lastFPS[0] = 1.f / clock.restart().asSeconds();
		std::rotate(lastFPS.begin(), lastFPS.begin() + 1, lastFPS.end());
		float mediumFPS = calculateMediumFPS(lastFPS);
		window.setTitle(std::to_string(static_cast<int>(mediumFPS)));
		clock.restart();
		
		sf::Event event{};
		while(window.pollEvent(event)) {
			ui::handleEvent(event);
			
			if(event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		window.update();
		ui::clearEvent();
	}
}
