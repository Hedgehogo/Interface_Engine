#include "window.hpp"
#include "ui/sfmlEvents/handleEvent/handleEvent.hpp"

namespace ui {
	IWindowResizer* getWindowResizer() {
		return new WindowResizer{};
	}
	
	void Window::construction() {
		resizer->setWindow(this);
		interface.init(window);
		reCreateMinSize();
		
		auto size{max(sf::Vector2u(minSize), window.getSize())};
		
		sf::View view{sf::Vector2f{size / 2u}, sf::Vector2f{size}};
		window.setView(view);
		interface.setSize(sf::Vector2f{size});
	}
	
	Window::Window(const Interface& interface) : interface(interface), resizer(getWindowResizer()) {
		construction();
		this->interface.setRenderWindowSize(window);
	}
	
	Window::Window(const Interface& interface, const sf::String& title, const sf::VideoMode& mode, const sf::ContextSettings& settings) :
		interface(interface),
		window(
			(mode == sf::VideoMode{} ? [&] {
				auto newWindowSize{interface.getNormalSize()};
				setSize({static_cast<unsigned>(std::ceil(newWindowSize.x)), static_cast<unsigned>(std::ceil(newWindowSize.y))});
				return sf::VideoMode{static_cast<unsigned>(std::ceil(newWindowSize.x)), static_cast<unsigned>(std::ceil(newWindowSize.y))};
			}() : mode), title, sf::Style::None, settings
		), resizer(getWindowResizer()) {
		construction();
	}
	
	Window::Window(const Interface& interface, const sf::String& title, const sf::ContextSettings& settings) :
		interface(interface),
		window(
			[&] {
				auto newWindowSize{interface.getNormalSize()};
				setSize({static_cast<unsigned>(std::ceil(newWindowSize.x)), static_cast<unsigned>(std::ceil(newWindowSize.y))});
				return sf::VideoMode{static_cast<unsigned>(std::ceil(newWindowSize.x)), static_cast<unsigned>(std::ceil(newWindowSize.y))};
			}(), title, sf::Style::None, settings
		), resizer(getWindowResizer()) {
		construction();
	}
	
	Window::Window(const Interface& interface, sf::WindowHandle handle, const sf::ContextSettings& settings) :
		interface(interface), window(handle, settings), resizer(getWindowResizer()) {
		construction();
		this->interface.setRenderWindowSize(window);
	}
	
	Window::Window(const std::filesystem::path& interface) : interface(makeInterface(interface)), resizer(getWindowResizer()) {
		construction();
		this->interface.setRenderWindowSize(window);
	}
	
	Window::Window(const std::filesystem::path& interface, const sf::String& title, const sf::VideoMode& mode, const sf::ContextSettings& settings) :
		interface(makeInterface(interface)), window(mode, title, sf::Style::None, settings), resizer(getWindowResizer()) {
		construction();
		this->interface.setRenderWindowSize(window);
	}
	
	Window::Window(const std::filesystem::path& interface, const sf::String& title, const sf::ContextSettings& settings) :
		interface(makeInterface(interface)), window({1, 1}, title, sf::Style::None, settings), resizer(getWindowResizer()) {
		construction();
		this->interface.setRenderWindowSize(window);
	}
	
	Window::Window(const std::filesystem::path& interface, sf::WindowHandle handle, const sf::ContextSettings& settings) :
		interface(makeInterface(interface)), window(handle, settings), resizer(getWindowResizer()) {
		construction();
		this->interface.setRenderWindowSize(window);
	}
	
	Window::Window(Interface::Make&& interface, const sf::String& title, const sf::VideoMode& mode, const sf::ContextSettings& settings) :
		interface(window, std::move(interface.object), std::move(interface.animationManager), std::move(interface.interactionStack)),
		window(
			[&] {
				if(mode == sf::VideoMode{}) {
					auto newWindowSize{this->interface.getNormalSize()};
					setSize({static_cast<unsigned>(std::ceil(newWindowSize.x)), static_cast<unsigned>(std::ceil(newWindowSize.y))});
					return sf::VideoMode{static_cast<unsigned>(std::ceil(newWindowSize.x)), static_cast<unsigned>(std::ceil(newWindowSize.y))};
				}
				return mode;
			}(), title, sf::Style::None, settings
		), resizer(getWindowResizer()) {
		auto size{max(sf::Vector2u(minSize), window.getSize())};
		resizer->setWindow(this);
		Window::reCreateMinSize();
		sf::View view{sf::Vector2f{size / 2u}, sf::Vector2f{size}};
		window.setView(view);
		this->interface.setSize(sf::Vector2f{size});
	}
	
	void Window::create(sf::VideoMode mode, const sf::String& title, sf::Uint32, const sf::ContextSettings& settings) {
		window.create(mode, title, sf::Style::None, settings);
	}
	
	void Window::create(sf::VideoMode mode, const sf::String& title, const sf::ContextSettings& settings) {
		Window::create(mode, title, sf::Style::None, settings);
	}
	
	void Window::reCreateMinSize() {
		minSize = this->interface.getMinSize();
		minSize = {std::ceil(minSize.x), std::ceil(minSize.y)};
		minSize = max(minSize, {1, 1});
	}
	
	void Window::update() {
		KeyHandler::updateMouse();
		sf::Vector2i mousePosition{sf::Mouse::getPosition(window)};
		
		bool resizerUpdated = resizer->update(mousePosition);
		
		window.clear();
		interface.update(sf::Vector2f{(mousePosition)}, !resizerUpdated && window.hasFocus());
		interface.draw();
		//interface.drawDebug(window, 0, 2, 90, 90);
		window.display();
		
		KeyHandler::clearGlobalKeys();
	}
	
	Interface& Window::getInterface() {
		return interface;
	}
	
	sf::RenderWindow& Window::getWindow() {
		return window;
	}
	
	const sf::Vector2f& Window::getMinSize() {
		return minSize;
	}
	
	void Window::setSize(const sf::Vector2u& size) {
		sf::View view{sf::Vector2f{size / 2u}, sf::Vector2f{size}};
		window.setSize(size);
		window.setView(view);
		interface.setSize(sf::Vector2f{size});
	}
}