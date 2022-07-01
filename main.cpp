#include <iostream>
#include "UI.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(400, 200), "IE works!");
	sf::View view(sf::Vector2f(0, 0), static_cast<sf::Vector2f>(window.getSize()));
	//window.setFramerateLimit(60);
	
	sf::Texture texture;
	texture.loadFromFile("image.png");
	sf::Texture texture_2;
	texture_2.loadFromFile("image_2.png");
	sf::Font font;
	font.loadFromFile("segoeui.ttf");
	
	ui::Caption::setDefaultColor(sf::Color::White);
	ui::Caption::setDefaultSize(15);
	
	ui::ButtonWithPanel* buttonWithPanel {
		new ui::ButtonWithPanel {
			new ui::Panel {
				new ui::ButtonWithPanel {
					new ui::Panel {
						new ui::LayerWithConstBezel {
							new ui::Text{
                                {
                                    new ui::InteractiveTextBlock{
                                        0,
                                        L"соси жопу грёбаный убюдок мать твою, иди сюда блять"
                                    }
                                },
                                new ui::FullColor{{60, 63, 65}},
                                14,
                                1.15,
                                &font,
                                sf::Color::Green
                            },
							new ui::FullColor{{81, 81, 81}},
							1
						},
						new ui::PointingHidePanelInteraction{},
						new ui::Sizing2{new ui::RelativeParentSizing{}, new ui::ConstSizing{100}},
						new ui::Positioning2{ui::Location2::downLeft, ui::Location2::upLeft, {0, -1}}
					},
					new ui::PointingDisplayPanelInteraction{},
					new ui::LayerWithConstBezel {
						new ui::FullColor{{60, 63, 65}},
						new ui::FullColor{{81, 81, 81}},
						1
					},
				},
				new ui::ClickHidePanelInteraction{sf::Mouse::Left},
				new ui::Sizing2{new ui::RelativeParentSizing{}, new ui::RelativeParentSizing{}},
				new ui::Positioning2{ui::Location2::upRight, ui::Location2::upLeft, {0, -1}}
			},
			new ui::PointingDisplayPanelInteraction{},
			new ui::FullColor{{78, 82, 84}}
		},
	};
	
	ui::Interface interface {
		new ui::LayerWithConstBorder {
			new ui::Slider {
				new ui::Capsule({78, 78, 78}),
				new ui::FullColor({43, 43, 43}),
				sf::Vector2f{1.0f, 0.5f}
			},
			new ui::LayerWithConstRatio {
				new ui::LayerWithConstBezel {
					new ui::LayerWithConstBorder {
						new ui::LayerWithBorderVertical {
							{
								buttonWithPanel,
								new ui::FullColor{{60, 63, 65}},
								buttonWithPanel->copy()
							}
						},
						new ui::FullColor{{60, 63, 65}},
						ui::Side::Up, 81
					},
					new ui::FullColor{{50, 50, 50}}, 1
				},
				new ui::FullColor{{43, 43, 43}},
				new ui::FullColor{{43, 43, 43}},
				1.f / 3.f, ui::Corner::UpLeft
			},
			ui::Side::Right, 10
		},
		new ui::InteractionStack {
			std::vector<ui::IInteraction *> {
				ui::MouseLambdaInteraction::debug.copy()
			}
		},
		window
	};
	
	interface.init();
	
	sf::Clock clock;
	while(window.isOpen()) {
		
		float currentTime = clock.restart().asSeconds();
        float fps = 1.f / currentTime;
        window.setTitle(std::to_string(static_cast<int>(fps)));
		
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
