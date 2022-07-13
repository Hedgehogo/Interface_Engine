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
    sf::Texture texture_3;
    texture_3.loadFromFile("image_3.png");
	sf::Font font;
	font.loadFromFile("segoeui.ttf");
	
	ui::Caption::setDefaultColor(sf::Color::White);
	ui::Caption::setDefaultSize(15);
	
	ui::Interface interface {
		new ui::LayerWithMovableBorder{
			new ui::LayerWithMovableBorder{
				new ui::LayerWithBorderHorizontal{
					{
						new ui::FullColor{{22, 22, 22}},
						new ui::LayerWithConstRatio{
							new ui::LayerWithAlternativeObject{
								new ui::ButtonWithPanel{
									new ui::Panel{
										new ui::Text{
											{
												new ui::TextBlock{
													L"это собственность Артёма"
												}
											},
											new ui::RoundedRectangle{sf::Color(0xffffffff), 10},
											14,
											1.15,
											&font,
											sf::Color{10, 10, 0},
											sf::Color{200, 200, 200},
											sf::Color{200, 200, 200},
											ui::Text::Align::center
										}
										/*new ui::FullColor{sf::Color(0xffffffff)}*/,
										new ui::PointingHidePanelInteraction,
										new ui::Sizing2{
											sf::Vector2f{1, 0.5},
											sf::Vector2f{}
										},
										new ui::Positioning2{
											ui::Location2::right,
											ui::Location2::left
										}
									},
									new ui::PointingDisplayPanelInteraction,
									new ui::LayerWithRenderTexture{
										new ui::Sprite{texture_2}
									}
								},
								new ui::LayerWithBorderVertical{
									new ui::Empty,
									new ui::FullColor{sf::Color(0x9f6e5cff)}
								},
							},
							new ui::FullColor{{22, 22, 22}},
							new ui::FullColor{{22, 22, 22}},
							1,
							ui::Corner::DownLeft
						},
						new ui::FullColor{{22, 22, 22}}
					},
					std::vector<float>{
						0.4,
						0.6
					}
				},
				new ui::LayerWithBorderHorizontal{
					{
						new ui::FullColor{{22, 22, 22}},
						new ui::Text{
							{
								new ui::TextBlock{
									L"Box2D is a 2D rigid body simulation library for games. Programmers can use it in their games to make objects move in realistic ways and make the game world more interactive. From the game engine's point of view, a physics engine is just a system for procedural animation. \nBox2D is written in portable C++. Most of the types defined in the engine begin with the b2 prefix. Hopefully this is sufficient to avoid name clashing with your game engine."
								}
							},
							new ui::FullColor{sf::Color(0x9f6e5cff)},
							14,
							1.15,
							&font,
							sf::Color{10, 10, 0},
							sf::Color{200, 200, 200},
							sf::Color{200, 200, 200},
							ui::Text::Align::center
						},
						new ui::FullColor{{22, 22, 22}}
					},
					std::vector<float>{
						0.4,
						0.6
					}
				},
				false
			},
			new ui::LayerWithConstCenter{
				new ui::LayerWithAlternativeObject{
					new ui::LayerWithBorderHorizontal{
						{
							new ui::LayerWithAlternativeObject{
								new ui::Sprite{texture_3},
								new ui::Capsule{sf::Color(0x9f6e5cff)}
							},
							new ui::LayerWithAlternativeObject{
								new ui::Sprite{texture_3},
								new ui::Capsule{sf::Color(0x9f6e5cff)}
							}
						},
						{   0.5}
					},
					new ui::LayerWithBorderVertical{
						{
							new ui::LayerWithBorderHorizontal{
								{
									new ui::Empty,
									new ui::FullColor{sf::Color(0x9f6e5cff)},
									new ui::Empty
								},
								std::vector<float>{
									0.25,
									0.75
								}
							},
							new ui::Empty
						}
					}
				},
				new ui::FullColor{{22, 22, 22}},
				2
			},
			false,
			0.75
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
		interface.drawDebug(window, 0, 1, 0, 60);
		window.display();
	}
}
