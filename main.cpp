#include <iostream>
#include <array>
#include "lib/ui/UI.hpp"

template<typename I, I T>
float calculateMediumFPS(std::array<float, T> lastFPS) {
	float sum = 0.0f;
	for(const auto &fps: lastFPS) {
		sum += fps;
	}
	return sum / static_cast<float>(lastFPS.size());
}

int main() {
	ui::yamlBuilderInit();
	
    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;
	
    sf::RenderWindow window(sf::VideoMode(400, 200), "IE works!", sf::Style::Default, settings);
	sf::View view(sf::Vector2f(0, 0), static_cast<sf::Vector2f>(window.getSize()));
	window.setFramerateLimit(60);
	
	ui::Caption::setDefaultColor(sf::Color::White);
	ui::Caption::setDefaultSize(15);
	ui::BasePanel::setFullDebug(true);
	ui::Character::setDebug(true);
	
	ui::Interface interface {
		ui::loadFromYaml<ui::IScalable>("../example-resources/test.yaml"),
		new ui::InteractionStack {
			std::vector<ui::IInteraction *> {
				ui::MouseLambdaInteraction::debug.copy(),
//				new ui::OneButtonInteraction( new ui::ChangeObjectEvent { testVariable->getValue(), 1 }, ui::Key::mouseLeft)
			}
		}
	};
	
	interface.init(window);
    window.setSize(sf::Vector2u(ui::max(interface.getNormalSize(), {1, 1})));
    interface.setSize(ui::max(interface.getNormalSize(), {1, 1}));
	
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
			
			if(event.type == sf::Event::Resized) {
				sf::Vector2f minSize = interface.getMinSize();
				sf::Vector2f windowSize{static_cast<float>(event.size.width), static_cast<float>(event.size.height)};
				if(windowSize.x < minSize.x || windowSize.y < minSize.y) {
					windowSize = ui::max(windowSize, minSize);
					window.setSize(static_cast<sf::Vector2u>(windowSize));
				}
				view.reset({{}, windowSize});
				window.setView(view);
				interface.setSize(windowSize);
			}
			if(event.type == sf::Event::MouseWheelMoved) {
				sf::Wheel::value = event.mouseWheel.delta;
			}
		}
        interface.setSize(sf::Vector2f{window.getSize()});
		window.clear();
		interface.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)), window.getSystemHandle());
		interface.draw();
		//interface.drawDebug(window, 0, 2, 90, 90);
		window.display();
        ui::clearEvent();
	}
}
