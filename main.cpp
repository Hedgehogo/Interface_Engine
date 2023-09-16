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
		ie::Interface{
			makeBoxPtr<ie::BoxScroll>(
				makeBoxPtr<ie::Text>(
					ie::makeVector(
						makeBoxPtr<ie::BaseTextBlock, ie::TextBlock>(
							U"["
						),
						makeBoxPtr<ie::BaseTextBlock, ie::TextBlock>(
							U"aaa",
							sf::Color::Black,
							orl::Option<sf::Font*>{},
							sf::Text::Style{},
							ie::makeVector (
								makeBoxPtr<ie::BaseLine, ie::Underline>(sf::Color::Red)
							)
						),
						makeBoxPtr<ie::BaseTextBlock, ie::TextBlock>(
							U"] [",
							sf::Color::Black,
							orl::Option<sf::Font*>{},
							sf::Text::Style{},
							ie::makeVector (
								makeBoxPtr<ie::BaseLine, ie::StrikeThrough>(sf::Color::Black, 0.15f)
							)
						),
						makeBoxPtr<ie::BaseTextBlock, ie::InteractiveTextBlock>(
							makeBoxPtr<ie::OneKeyInteraction>(
								makeBoxPtr<ie::OpenUrlAction>(
									"https://github.com/Hedgehogo/Interface_Engine/"
								),
								ie::Key::mouseLeft
							),
							U"bbb",
							sf::Color::Black,
							orl::Option<sf::Font*>{},
							sf::Text::Style{},
							ie::makeVector (
								makeBoxPtr<ie::BaseLine, ie::StrikeThrough>(sf::Color::Blue)
							)
						),
						makeBoxPtr<ie::BaseTextBlock, ie::TextBlock>(
							U"] "
						),
						makeBoxPtr<ie::BaseTextBlock, ie::ObjectTextBlock>(
							makeBoxPtr<ie::FullColor>(sf::Color::Red),
							sf::Vector2f{100, 100}
						),
						makeBoxPtr<ie::BaseTextBlock, ie::ObjectTextBlock>(
							makeBoxPtr<ie::BoxConstBezel>(
								makeBoxPtr<ie::BoxScroll>(
									makeBoxPtr<ie::Text>(
										ie::makeVector(
											makeBoxPtr<ie::BaseTextBlock, ie::TextBlock>(
												U"Text in text!"
											)
										),
										makeBoxPtr<ie::FullColor>(sf::Color::White),
										30,
										&font,
										sf::Color::Red,
										sf::Color::White,
										sf::Color::Blue,
										sf::Color::Red,
										sf::Color{150, 150, 150},
										sf::Text::Style{},
										makeBoxPtr<ie::Resizer>(1.15f, ie::BaseResizer::Align::Center)
									),
									a_value
								),
								makeBoxPtr<ie::FullColor>(sf::Color::Green),
								10.f
							),
							100.f
						)
					),
					makeBoxPtr<ie::FullColor>(sf::Color::White),
					30,
					&font,
					sf::Color::Black,
					sf::Color::White,
					sf::Color::Blue,
					sf::Color::Black,
					sf::Color{150, 150, 150},
					sf::Text::Style{},
					makeBoxPtr<ie::Resizer>(1.15f, ie::BaseResizer::Align::Left),
					makeBoxPtr<ie::BasicHotkeyInteraction<ie::Text&>>(
						ie::makeVector(
							ie::makeVector(
								makeBoxPtr<ie::detail::BasicHotkeyInteractionHotkey<ie::Text&>>(
									makeBoxPtr<ie::BasicKeysInteraction<ie::Text&>>(
										makeBoxPtr<ie::TextSelectionAction>(),
										std::vector{ie::Key::mouseLeft}
									)
								),
								makeBoxPtr<ie::detail::BasicHotkeyInteractionHotkey<ie::Text&>>(
									makeBoxPtr<ie::BasicKeysInteraction<ie::Text&>>(
										makeBoxPtr<ie::TextCopyAction>(),
										std::vector{ie::Key::lControl, ie::Key::c}
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
