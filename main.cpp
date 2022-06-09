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
	
	ui::Caption::setDefaultColor(sf::Color::White);
	ui::Caption::setDefaultSize(15);
	ui::Interface interface {
		/*new ui::LayerWithConstBorder {
			new ui::FullColor{sf::Color::Cyan},
			new ui::LayerWithConstRatio {
				new ui::LayerWithConstRatio {
					new ui::Sprite{sprite, sf::Vector2f(0, 0), texture},
					new ui::FullColor{sf::Color::Red},
					new ui::FullColor{sf::Color::Yellow},
					0.8f,
					ui::LayerWithConstRatio::UpLeft,
					{0, 0}
				},
				new ui::LayerWithBorder {
					{
						{
							new ui::FullColor{sf::Color::Green},
							new ui::FullColor{sf::Color::Yellow},
							new ui::FullColor{sf::Color::Red}
						},
						{
							new ui::FullColor{sf::Color::Blue},
							new ui::Sprite{sprite, sf::Vector2f(0, 0), texture_2},
							new ui::Button {
								new ui::FullColor{sf::Color::Blue}, 0, sf::Vector2f(0, 0)
							}
						}
					},
					{0.5f},
					{0.3f, 0.8f},
					{0, 0}
				},
				new ui::FullColor{sf::Color::Magenta},
				0.5f,
				ui::LayerWithConstRatio::UpRight,
				{0, 0}
			},
			ui::LayerWithConstBorder::Side::Left, 20, {50, 50}
		}*/
		new ui::LayerWithConstBorder {
			new ui::Slider {
				new ui::Capsule({200, 200, 200}),
				new ui::FullColor({37, 37, 38}),
				sf::Vector2f{1.0f, 0.5f}
			},
			new ui::ButtonWithPanel {
				new ui::Panel {
					new ui::FullColor{{200, 200, 200}},
					sf::Vector2f{50, 50}
				},
				new ui::PointingDisplayPanelInteraction{},
				new ui::FullColor{{37, 37, 38}}
			},
			ui::Side::Right, 10
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