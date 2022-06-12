#include <iostream>
#include "UI.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(400, 200), "SFML works!");
	sf::View view(sf::Vector2f(0, 0), static_cast<sf::Vector2f>(window.getSize()));
	
	sf::Texture texture;
	texture.loadFromFile("image.png");
	sf::Texture texture_2;
	texture_2.loadFromFile("image_2.png");
	sf::Sprite sprite;
	sf::Font font;
	font.loadFromFile("segoeui.ttf");

    const std::wstring text = L"Ass";

	
	ui::Caption::setDefaultColor(sf::Color::White);
	ui::Caption::setDefaultSize(15);
	ui::Interface interface {
        new ui::LayerWithBorderVertical{
            {
                new ui::Text{
                    {
                        new ui::TextBlock{
                            L"Исполнитель ",
                            sf::Color::White
                        },
                        new ui::TextBlock{
                            L"Робот",
                            sf::Color::Red,
                            sf::Text::Style::Bold
                        },
                        new ui::TextBlock{
                            L"действует на клетчатой доске, между соседними клетками которой могут стоять стены. Робот передвигается по клеткам доски и может выполнять команды 1 (вверх), 2 (вниз), 3 (вправо) и 4 (влево), переходя на соседнюю клетку в направлении, указанном в скобках. Если в этом направлении между клетками стоит стена, то Робот разрушается. Робот успешно выполнил программу \n1132432 \nКакую последовательность из трех команд должен выполнить Робот, чтобы вернуться в ту клетку, где он был перед началом выполнения программы, и не разрушиться вне зависимости от того, какие стены стоят на поле?",
                            sf::Color::White
                        }
                    },
                    new ui::FullColor(sf::Color::Black),
                    14,
                    14,
                    &font,
                    ui::Text::Align::left
                },
                new ui::FullColor(sf::Color::Cyan)
            },
            {
                0.5
            }
        },
		InteractionStack {
			std::vector<ui::IInteraction *> {
				new ui::MouseLambdaInteraction {
					new ui::ButtonEvent_LambdaSimple {
						[](sf::Vector2i) {std::cout << "sl";},
						[](sf::Vector2i) {std::cout << "wl";},
						[](sf::Vector2i) {std::cout << "sl";},
						[](sf::Vector2i) {std::cout << "nl";}
					},
					new ui::ButtonEvent_LambdaSimple {
						[](sf::Vector2i) {std::cout << "sr" << std::endl;},
						[](sf::Vector2i) {std::cout << "wr" << std::endl;},
						[](sf::Vector2i) {std::cout << "sr" << std::endl;},
						[](sf::Vector2i) {std::cout << "nr" << std::endl;}
					},
					[](sf::Vector2i) {std::cout << "sp" << std::endl;},
					[](sf::Vector2i) {std::cout << "fp" << std::endl;}
				},
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