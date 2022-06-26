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
	
	/*ui::ButtonWithPanel* buttonWithPanel {
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
						ui::Corner::DownLeft, ui::Corner::UpLeft, {0, -1},
						ui::Size::constant, ui::Size::regardingParent, sf::Vector2f{0, 100}
					},
					new ui::PointingDisplayPanelInteraction{},
					new ui::LayerWithConstBezel {
						new ui::FullColor{{60, 63, 65}},
						new ui::FullColor{{81, 81, 81}},
						1
					},
				},
				new ui::ClickHidePanelInteraction{sf::Mouse::Left},
				ui::Corner::UpRight, ui::Corner::UpLeft, {-5, 5},
				ui::Size::regardingParent, ui::Size::regardingParent,sf::Vector2f{50, 50},
			},
			new ui::PointingDisplayPanelInteraction{},
			new ui::FullColor{{78, 82, 84}}
		},
	};*/
	
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
		/*new ui::LayerWithConstBorder {
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
		}*/
		/*new  ui::LayerWithMovableBorder{
			new ui::LayerWithMovableBorder{
				new ui::LayerWithBorderHorizontal{
					{
						new ui::FullColor{{22, 22, 22}},
						new ui::LayerWithConstRatio{
							new ui::LayerWithAlternativeObject{
								new ui::Sprite{texture_2},
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
					std::vector<float> {
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
									L" \n \n \n \n \nBox2D is a 2D rigid body simulation library for games. Programmers can use it in their games to make objects move in realistic ways and make the game world more interactive. From the game engine's point of view, a physics engine is just a system for procedural animation. \nBox2D is written in portable C++. Most of the types defined in the engine begin with the b2 prefix. Hopefully this is sufficient to avoid name clashing with your game engine."
								}
							},
							new ui::FullColor{sf::Color(0x9f6e5cff)},
							14,
							1.15,
							&font,
							sf::Color{255, 255, 0},
							sf::Color{200, 200, 200},
							sf::Color{200, 200, 200},
							ui::Text::Align::right
						},
						new ui::FullColor{{22, 22, 22}}
					},
					std::vector<float> {
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
							new ui::Capsule{sf::Color(0x9f6e5cff)},
							new ui::Capsule{sf::Color(0x9f6e5cff)}
						},
						{0.5}
					},
					new ui::LayerWithBorderVertical{
						{
							new ui::LayerWithBorderHorizontal{
								{
									new ui::Empty,
									new ui::FullColor{sf::Color(0x9f6e5cff)},
									new ui::Empty
								},
								std::vector<float> {
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
		}*/
        new ui::LayerWithAlternativeObject{
            new ui::LayerWithBorderHorizontal{
                {
                    new ui::Empty,
                    new ui::LayerWithBorderVertical{
                        {
                            new ui::Text{
                                {
                                    new ui::TextBlock{
                                        L"In games, it is not uncommon to have levels which are much bigger than the window itself. You only see is a small part of them. This is typically the case in RPGs, platform games, and many other genres. What developers might tend to forget is that they define entities in a 2D world, not directly in the window. The window is just a view, it shows a specific area of the whole world. It is perfectly fine to draw several views of the same world in parallel, or draw the world to a texture rather than to a window. The world itself remains unchanged, what changes is just the way it is seen.\n\nSince what is seen in the window is just a small part of the entire 2D world, you need a way to specify which part of the world is shown in the window. Additionally, you may also want to define where/how this area will be shown within the window. These are the two main features of SFML views.\n\nTo summarize, views are what you need if you want to scroll, rotate or zoom your world. They are also the key to creating split screens and mini-maps.\n"
                                    }
                                },
                                new ui::FullColor{{255, 255, 255}},
                                14,
                                1.15,
                                &font,
                                sf::Color{0, 0, 0},
                                sf::Color{200, 200, 200},
                                sf::Color{200, 200, 200},
                                ui::Text::Align::left
                            },
                            new ui::Text{
                                {
                                    new ui::TextBlock{
                                        L"Copies the elements in the range, defined by [first, last), to another range beginning at d_first.\n\n1) Copies all elements in the range [first, last) starting from first and proceeding to last - 1. The behavior is undefined if d_first is within the range [first, last). In this case, std::copy_backward may be used instead.\n3) Only copies the elements for which the predicate pred returns true. The relative order of the elements that are copied is preserved. The behavior is undefined if the source and the destination ranges overlap.\n2,4) Same as (1,3), but executed according to policy. These overloads do not participate in overload resolution unless std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> (until C++20) std::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> (since C++20) is true."
                                    }
                                },
                                new ui::FullColor{{0, 0, 0}},
                                14,
                                1.15,
                                &font,
                                sf::Color{255, 255, 255},
                                sf::Color{200, 200, 200},
                                sf::Color{200, 200, 200},
                                ui::Text::Align::center,

                            },
                            new ui::Text{
                                {
                                    new ui::TextBlock{
                                        L"Все начинается с загрузки с сайта. Линк на загрузку найти не так просто - все спрятано за предложением shareware версий, попыток заставить пройти регистрацию, анкетирование и черт знает еще чего. Все-же найдя мааленькую кнопку на скачивание и вытянув гигабайт фреймворка, внезапно, он отказывается ставиться и требует скачать онлайн версию.\n\nМэйнтейн ниже плинтуса. Qt Creator в windows xp запускается после кучи сообщений о несуществующей функции в dll. Предыдущая версия запускалась нормально, но пока проект не открыт, background не перерисовывался. Прогресс. Попытка собрать пустой проект приводит к крашу в отладке. К счастью, релиз кое-как работает.\n\nQSerialPort в windows работает через задницу. Если раньше известной багой было дублирование данных после flush и это обходилось костылями, то сейчас не работает и без flush. Не очень понятно, зачем такой глючный пакет нужно было включать в основную сборку?"
                                    }
                                },
                                new ui::FullColor{{255, 255, 255}},
                                14,
                                1.15,
                                &font,
                                sf::Color{0, 0, 0},
                                sf::Color{200, 200, 200},
                                sf::Color{200, 200, 200},
                                ui::Text::Align::right
                            }
                        }
                    },
                    new ui::Empty
                },
                std::vector<float>{
                    0.2,
                    0.8
                }
            },
            new ui::FullColor{{255, 0, 0}}
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
