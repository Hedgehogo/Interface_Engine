#include "IE/IE.hpp"
#include "IE/event/Event/Event.hpp"
#include <iostream>
#include <array>

template<size_t N>
class FpsCounter {
public:
	auto medium() -> float {
		auto sum{0.0f};
		for(auto const& fps: last_fps_) {
			sum += fps;
		}
		return sum / static_cast<float>(last_fps_.size());
	}
	
	auto restart() -> float {
		last_fps_[0] = 1.f / clock_.restart().asSeconds();
		std::rotate(last_fps_.begin(), last_fps_.begin() + 1, last_fps_.end());
		auto result{medium()};
		clock_.restart();
		return result;
	}

private:
	sf::Clock clock_;
	std::array<float, N> last_fps_{};
};

auto main() -> int {
	ie::init();
	
	auto font{sf::Font{}};
	font.loadFromFile("../../example-resources/segoeui.ttf");
	auto window{
		ie::make_window(
			"../../example-resources/test",
			"IEML works!",
			{800, 600},
			sf::ContextSettings{
				0, 0, 1
			}
		)
	};
	
	auto fps{FpsCounter<500>{}};
	
	while(window.get_window().isOpen()) {
		window.get_window().setTitle(std::to_string(fps.restart()));
		
		auto event{sf::Event{}};
		while(window.get_window().pollEvent(event)) {
			window.handle_event(event);
			
			if(event.type == sf::Event::Closed) {
				window.get_window().close();
			}
		}
		
		window.update();
		ie::clear_event();
	}
}
