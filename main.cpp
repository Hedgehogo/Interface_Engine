#include "IE/IE.hpp"
#include <iostream>
#include <array>

template<size_t N>
class FpsCounter {
public:
	float medium() {
		float sum = 0.0f;
		for(const auto& fps: last_fps_) {
			sum += fps;
		}
		return sum / static_cast<float>(last_fps_.size());
	}
	
	float restart() {
		last_fps_[0] = 1.f / clock_.restart().asSeconds();
		std::rotate(last_fps_.begin(), last_fps_.begin() + 1, last_fps_.end());
		float result = medium();
		clock_.restart();
		return result;
	}

private:
	sf::Clock clock_;
	std::array<float, N> last_fps_{};
};

int main() {
	ie::init();
	
	sf::Font font{};
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
	
	FpsCounter<500> fps;
	
	while(window.get_window().isOpen()) {
		window.get_window().setTitle(std::to_string(fps.restart()));
		
		sf::Event event{};
		while(window.get_window().pollEvent(event)) {
			ie::handle_event(event);
			
			if(event.type == sf::Event::Closed) {
				window.get_window().close();
			}
		}
		
		window.update();
		ie::clear_event();
	}
}
