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
	
	sf::Font font{};
	font.loadFromFile("../../example-resources/segoeui.ttf");
	auto a_value{std::make_shared<ie::SRVec2f>()};
	
	ie::Window window{
		ie::Interface::Make{
			make_box_ptr<ie::BoxScroll::Make>(
				make_box_ptr<ie::Text::Make>(
					ie::makeVector(
						make_box_ptr<ie::BaseTextBlock::Make, ie::TextBlock::Make>(
							U"bbabb"
						),
						make_box_ptr<ie::BaseTextBlock::Make, ie::TextBlock::Make>(
							U"bbbbb"
						)
					),
					&font,
					make_box_ptr<ie::FullColor::Make>(sf::Color::White),
					30U,
					sf::Color::Black,
					sf::Color::White,
					sf::Color::Blue,
					sf::Color::Black,
					sf::Color{150, 150, 150},
					sf::Text::Style{},
					make_box_ptr<ie::Resizer::Make>(1.15f, ie::BaseResizer::Align::Left),
					make_box_ptr<ie::BasicHotkeyInteraction<ie::Text&>::Make>(
						ie::makeVector(
							ie::makeVector(
								make_box_ptr<ie::detail::BasicHotkeyInteractionHotkey<ie::Text&>::Make>(
									make_box_ptr<ie::BasicKeysInteraction<ie::Text&>::Make>(
										make_box_ptr<ie::TextSelectionAction::Make>(),
										std::vector{ie::Key::MouseLeft}
									)
								),
								make_box_ptr<ie::detail::BasicHotkeyInteractionHotkey<ie::Text&>::Make>(
									make_box_ptr<ie::BasicKeysInteraction<ie::Text&>::Make>(
										make_box_ptr<ie::TextCopyAction::Make>(),
										std::vector{ie::Key::LControl, ie::Key::C}
									)
								)
							)
						)
					)
				),
				a_value
			)
		},
		"IE works!",
		{800, 600},
		sf::ContextSettings{
			0, 0, 1
		}
	};
	
	FpsCounter<500> fps;
	
	while(window.getWindow().isOpen()) {
		window.getWindow().setTitle(std::to_string(fps.restart()));
		
		sf::Event event{};
		while(window.getWindow().pollEvent(event)) {
			ie::handle_event(event);
			
			if(event.type == sf::Event::Closed) {
				window.getWindow().close();
			}
		}
		
		window.update();
		ie::clear_event();
	}
}
