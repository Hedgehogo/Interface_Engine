#include "lib/IE/IE.hpp"
#include <iostream>
#include <array>

template<std::size_t N>
class FpsCounter {
public:
	float medium() {
		float sum = 0.0f;
		for(const auto& fps: lastFPS) {
			sum += fps;
		}
		return sum / static_cast<float>(lastFPS.size());
	}
	
	float restart() {
		lastFPS[0] = 1.f / clock.restart().asSeconds();
		std::rotate(lastFPS.begin(), lastFPS.begin() + 1, lastFPS.end());
		float result = medium();
		clock.restart();
		return result;
	}
	
private:
	sf::Clock clock;
	std::array<float, N> lastFPS{};
};

int main() {
	ie::init();
	
	auto c_value{std::make_shared<ie::SRVec2f>()};
	auto b_value{std::make_shared<ie::Sbool>(false)};
	ie::Window window{
		ie::Interface::Make{
			makeBoxPtr<ie::IScalable::Make, ie::BoxConstBorder::Make>(
				makeBoxPtr<ie::IScalable::Make, ie::BoxConstBorder::Make>(
					makeBoxPtr<ie::IScalable::Make, ie::Switcher::Make>(
						makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Yellow),
						makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Blue),
						b_value
					),
					makeBoxPtr<ie::IScalable::Make, ie::Slider::Make>(
						makeBoxPtr<ie::IUninteractive::Make, ie::Capsule::Make>(sf::Color::Red),
						makeBoxPtr<ie::IUninteractive::Make, ie::FullColor::Make>(sf::Color::Green),
						c_value
					),
					20.f, ie::Side::up
				),
				makeBoxPtr<ie::IScalable::Make, ie::BoxSwitch::Make>(
					makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Yellow),
					makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Blue),
					b_value
				),
				20.f, ie::Side::right
			)
		},
		"IE works!",
		{200, 100},
		sf::ContextSettings{
			0, 0, 1
		}
	};
	
	FpsCounter<500> fps;
	
	while(window.getWindow().isOpen()) {
		window.getWindow().setTitle(std::to_string(fps.restart()));
		
		sf::Event event{};
		while(window.getWindow().pollEvent(event)) {
			ie::handleEvent(event);
			
			if(event.type == sf::Event::Closed) {
				window.getWindow().close();
			}
		}
		
		window.update();
		ie::clearEvent();
	}
}
