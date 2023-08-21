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
	ui::init();
	
	auto c_value{std::make_shared<ui::SRVec2f>()};
	auto b_value{std::make_shared<ui::Sbool>(false)};
	ui::Window window{
		ui::Interface::Make{
			makeBoxPtr<ui::IScalable::Make, ui::BoxConstBorder::Make>(
				makeBoxPtr<ui::IScalable::Make, ui::BoxConstBorder::Make>(
					makeBoxPtr<ui::IScalable::Make, ui::Switcher::Make>(
						makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Yellow),
						makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Blue),
						b_value
					),
					makeBoxPtr<ui::IScalable::Make, ui::Slider::Make>(
						makeBoxPtr<ui::IUninteractive::Make, ui::Capsule::Make>(sf::Color::Red),
						makeBoxPtr<ui::IUninteractive::Make, ui::FullColor::Make>(sf::Color::Green),
						c_value
					),
					20.f, ui::Side::up
				),
				makeBoxPtr<ui::IScalable::Make, ui::BoxSwitch::Make>(
					makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Yellow),
					makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Blue),
					b_value
				),
				20.f, ui::Side::right
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
			ui::handleEvent(event);
			
			if(event.type == sf::Event::Closed) {
				window.getWindow().close();
			}
		}
		
		window.update();
		ui::clearEvent();
	}
}
