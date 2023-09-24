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
			makeBoxPtr<ie::BoxScroll::Make>(
				makeBoxPtr<ie::Text::Make>(
					ie::makeVector(
						makeBoxPtr<ie::BaseTextBlock::Make, ie::TextBlock::Make>(
							U"["
						),
						makeBoxPtr<ie::BaseTextBlock::Make, ie::TextBlock::Make>(
							U"a bb ccc dddd",
							sf::Color::Black,
							orl::Option<sf::Font*>{},
							sf::Text::Style{},
							ie::makeVector (
								makeBoxPtr<ie::BaseLine::Make, ie::Underline::Make>(sf::Color::Red)
							)
						),
						makeBoxPtr<ie::BaseTextBlock::Make, ie::TextBlock::Make>(
							U"]\n[",
							sf::Color::Black,
							orl::Option<sf::Font*>{},
							sf::Text::Style{},
							ie::makeVector (
								makeBoxPtr<ie::BaseLine::Make, ie::StrikeThrough::Make>(orl::Option<sf::Color>{}, 0.15f)
							)
						),
						makeBoxPtr<ie::BaseTextBlock::Make, ie::InteractiveTextBlock::Make>(
							makeBoxPtr<ie::OneKeyInteraction>(
								makeBoxPtr<ie::OpenUrlAction>(
									"https://github.com/Hedgehogo/Interface_Engine/"
								),
								ie::Key::MouseLeft
							),
							U"e ff ggg hhhh",
							sf::Color::Black,
							orl::Option<sf::Font*>{},
							sf::Text::Style{},
							ie::makeVector (
								makeBoxPtr<ie::BaseLine::Make, ie::StrikeThrough::Make>(sf::Color::Blue)
							)
						),
						makeBoxPtr<ie::BaseTextBlock::Make, ie::TextBlock::Make>(
							U"] "
						),
						makeBoxPtr<ie::BaseTextBlock::Make, ie::ObjectTextBlock::Make>(
							makeBoxPtr<ie::FullColor::Make>(sf::Color::Red),
							sf::Vector2f{100, 100}
						)
					),
					makeBoxPtr<ie::FullColor::Make>(sf::Color::White),
					30U,
					&font,
					sf::Color::Black,
					sf::Color::White,
					sf::Color::Blue,
					sf::Color::Black,
					sf::Color{150, 150, 150},
					sf::Text::Style{},
					makeBoxPtr<ie::Resizer::Make>(1.15f, ie::BaseResizer::Align::Left),
					makeBoxPtr<ie::BasicHotkeyInteraction<ie::Text&>::Make>(
						ie::makeVector(
							ie::makeVector(
								makeBoxPtr<ie::detail::BasicHotkeyInteractionHotkey<ie::Text&>::Make>(
									makeBoxPtr<ie::BasicKeysInteraction<ie::Text&>::Make>(
										makeBoxPtr<ie::TextSelectionAction::Make>(),
										std::vector{ie::Key::MouseLeft}
									)
								),
								makeBoxPtr<ie::detail::BasicHotkeyInteractionHotkey<ie::Text&>::Make>(
									makeBoxPtr<ie::BasicKeysInteraction<ie::Text&>::Make>(
										makeBoxPtr<ie::TextCopyAction::Make>(),
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
			ie::handleEvent(event);
			
			if(event.type == sf::Event::Closed) {
				window.getWindow().close();
			}
		}
		
		window.update();
		ie::clearEvent();
	}
}
