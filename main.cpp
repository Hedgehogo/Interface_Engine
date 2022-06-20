#include <iostream>
#include "UI.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(400, 200), "IE works!");
	sf::View view(sf::Vector2f(0, 0), static_cast<sf::Vector2f>(window.getSize()));
	sf::Texture texture;
	texture.loadFromFile("image.png");
	sf::Texture texture_2;
	texture_2.loadFromFile("image_2.png");
	sf::Sprite sprite;
	sf::Font font;
	font.loadFromFile("segoeui.ttf");
	
	ui::Caption::setDefaultColor(sf::Color::White);
	ui::Caption::setDefaultSize(15);
	ui::Interface interface {
        new ui::LayerWithBorderVertical{
            {
                new ui::Text{
                    {
                        new ui::TextBlock{
                            L"Съешь же ещё этих мягких французских булок да выпей чаю",
                            sf::Color::Red,
                            &font,
                            sf::Text::Style::Bold
                        }
                    },
                    new ui::FullColor(sf::Color::White),
                    14,
                    1.15,
                    &font,
                    sf::Color(0, 0, 0),
                    sf::Color(255, 255, 255),
                    sf::Color(255, 0, 0),
                    ui::Text::Align::left
                },
                new ui::Text{
                    {
                        new ui::TextBlock{
                            L"Съешь же ещё этих мягких французских булок да выпей чаю",
                            sf::Color::Red,
                            &font,
                            sf::Text::Style::Bold
                        }
                    },
                    new ui::FullColor(sf::Color::White),
                    14,
                    1.15,
                    &font,
                    sf::Color(0, 0, 0),
                    sf::Color(255, 255, 255),
                    sf::Color(255, 0, 0),
                    ui::Text::Align::right
                },
                new ui::Text{
                    {
                        new ui::TextBlock{
                            L"Съешь же ещё этих мягких французских булок да выпей чаю",
                            sf::Color::Red,
                            &font,
                            sf::Text::Style::Bold
                        }
                    },
                    new ui::FullColor(sf::Color::White),
                    14,
                    1.15,
                    &font,
                    sf::Color(0, 0, 0),
                    sf::Color(255, 255, 255),
                    sf::Color(255, 0, 0),
                    ui::Text::Align::center
                }
            }
        },
		ui::InteractionStack {
			std::vector<ui::IInteraction *> {
				ui::MouseLambdaInteraction::debug.copy()
			}
		},
		window
	};
	
	interface.init();
	
	while(window.isOpen()) {
		sf::Event event{};
		int wheel = 0;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed) {
				window.close();
			}
			if(event.type == sf::Event::Resized) {
				view.reset(sf::FloatRect(sf::Vector2f(0, 0), static_cast<sf::Vector2f>(window.getSize())));
				sf::Vector2f minSize = interface.getMinSize();
				sf::Vector2f windowSize{static_cast<float>(event.size.width), static_cast<float>(event.size.height)};
				if(windowSize.x < minSize.x || windowSize.y < minSize.y) {
					if(windowSize.x < minSize.x) {
						windowSize.x = minSize.x;
					}
					if(windowSize.y < minSize.y) {
						windowSize.y = minSize.y;
					}
					window.setSize(static_cast<sf::Vector2u>(windowSize));
				}
				window.setView(view);
				interface.resize(windowSize,sf::Vector2f(0, 0));
			}
			if(event.type == sf::Event::MouseWheelMoved) {
				wheel = event.mouseWheel.delta;
			}
		}
		window.clear();
		interface.update(wheel);
		interface.draw();
		window.display();
        
	}
}