#include "lib/IE/IE.hpp"
#include <iostream>
#include <array>

template<std::size_t N>
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
	auto a_value{std::make_shared<ie::SRVec2f>()};
	
	ie::Window window{
		ie::Interface::Make{
			make_box_ptr<ie::BoxScroll::Make>(
				make_box_ptr<ie::Text::Make>(
					ie::make_vector(
						make_box_ptr<ie::BaseTextBlock::Make, ie::TextBlock::Make>(
							U"The Interface_Engine project was created to easily write a scalable interface for games and programs in C++ 17 or more. At the same time it allows you to:\n"
							"\n"
							"Automatically calculate the minimum size at which the interface is displayed correctly.\n"
							"Automatically calculate the ideal size for displaying your interface.\n"
							"Before studying and using this library, we advise you to familiarize yourself with the basics of SFML.",
							orl::Option<sf::Color>{},
							orl::Option<sf::Font*>{},
							orl::Option<sf::Text::Style>{},
							ie::make_vector(
								make_box_ptr<ie::BaseLine::Make, ie::Underline::Make>(),
								make_box_ptr<ie::BaseLine::Make, ie::StrikeThrough::Make>()
							),
							30U
						),
						make_box_ptr<ie::BaseTextBlock::Make, ie::ObjectTextBlock::Make>(
							make_box_ptr<ie::FullColor::Make>(sf::Color::Red),
							100.f
						)
					),
					&font,
					make_box_ptr<ie::FullColor::Make>(sf::Color::White),
					14U,
					sf::Color::Black,
					sf::Color::White,
					sf::Color::Blue,
					sf::Color::Black,
					sf::Color{150, 150, 150},
					sf::Text::Style{},
					make_box_ptr<ie::Resizer::Make>(1.15f, ie::BaseResizer::Align::Center, ie::BaseResizer::Algorithm::Base),
					make_box_ptr<ie::BasicHotkeyInteraction<ie::Text&>::Make>(
						ie::make_vector(
							ie::make_vector(
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
		{800, 600}
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
