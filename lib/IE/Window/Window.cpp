#include "Window.hpp"
#include "IE/SfmlEvents/HandleEvent/HandleEvent.hpp"

namespace ui {
	BaseWindowResizer* getWindowResizer() {
		return new WindowResizer{};
	}
	
	void Window::construction() {
		resizer->setWindow(*this);
		interface.init(window);
		reCalculateMinSize();
		
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
		window(
			(mode == sf::VideoMode{} ? [&] {
				auto newWindowSize{interface.getNormalSize()};
				setSize({static_cast<unsigned>(std::ceil(newWindowSize.x)), static_cast<unsigned>(std::ceil(newWindowSize.y))});
				return sf::VideoMode{static_cast<unsigned>(std::ceil(newWindowSize.x)), static_cast<unsigned>(std::ceil(newWindowSize.y))};
			}() : mode), title, sf::Style::None, settings
		), interface(interface), resizer(getWindowResizer()) {
		construction();
	}
	
	Window::Window(const Interface& interface, const sf::String& title, const sf::ContextSettings& settings) :
		window(
			[&] {
				auto newWindowSize{interface.getNormalSize()};
				setSize({static_cast<unsigned>(std::ceil(newWindowSize.x)), static_cast<unsigned>(std::ceil(newWindowSize.y))});
				return sf::VideoMode{static_cast<unsigned>(std::ceil(newWindowSize.x)), static_cast<unsigned>(std::ceil(newWindowSize.y))};
			}(), title, sf::Style::None, settings
		), interface(interface), resizer(getWindowResizer()) {
		construction();
	}
	
	Window::Window(const Interface& interface, sf::WindowHandle handle, const sf::ContextSettings& settings) :
		window(handle, settings), interface(interface), resizer(getWindowResizer()) {
		construction();
		this->interface.setRenderWindowSize(window);
	}
	
	Window::Window(const std::filesystem::path& interface) : interface(makeInterface(interface)), resizer(getWindowResizer()) {
		construction();
		this->interface.setRenderWindowSize(window);
	}
	
	Window::Window(const std::filesystem::path& interface, const sf::String& title, const sf::VideoMode& mode, const sf::ContextSettings& settings) :
		window(mode, title, sf::Style::None, settings), interface(makeInterface(interface)), resizer(getWindowResizer()) {
		construction();
		this->interface.setRenderWindowSize(window);
	}
	
	Window::Window(const std::filesystem::path& interface, const sf::String& title, const sf::ContextSettings& settings) :
		window({1, 1}, title, sf::Style::None, settings), interface(makeInterface(interface)), resizer(getWindowResizer()) {
		construction();
		this->interface.setRenderWindowSize(window);
	}
	
	Window::Window(const std::filesystem::path& interface, sf::WindowHandle handle, const sf::ContextSettings& settings) :
		window(handle, settings), interface(makeInterface(interface)), resizer(getWindowResizer()) {
		construction();
		this->interface.setRenderWindowSize(window);
	}
	
	Window::Window(Interface::Make&& make, sf::String&& title, sf::VideoMode&& mode, sf::ContextSettings&& settings) :
		interface(window, std::move(make.object), std::move(make.animationManager), std::move(make.interactionStack)),
		resizer(getWindowResizer()) {
		
		Window::reCalculateMinSize();
		if(mode == sf::VideoMode{}) {
			sf::Vector2u normalSize{mapVector2<float, std::ceil>(this->interface.getNormalSize())};
			sf::Vector2u size{max(sf::Vector2u(minSize), normalSize)};
			mode = sf::VideoMode{size.x, size.y};
		}
		sf::Vector2u size{mode.width, mode.height};
		
		window.create(mode, title, sf::Style::None, settings);
		window.setView({sf::Vector2f{size / 2u}, sf::Vector2f{size}});
		interface.setSize(sf::Vector2f{size});
		resizer->setWindow(*this);
	}
	
	void Window::create(sf::VideoMode mode, const sf::String& title, sf::Uint32, const sf::ContextSettings& settings) {
		window.create(mode, title, sf::Style::None, settings);
	}
	
	void Window::create(sf::VideoMode mode, const sf::String& title, const sf::ContextSettings& settings) {
		Window::create(mode, title, sf::Style::None, settings);
	}
	
	void Window::reCalculateMinSize() {
		minSize = max(sf::Vector2u{mapVector2<float, std::ceil>(this->interface.getMinSize())}, {1, 1});
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
	
	sf::Vector2u Window::getMinSize() const {
		return minSize;
	}
	
	void Window::setSize(const sf::Vector2u& size) {
		sf::View view{sf::Vector2f{size / 2u}, sf::Vector2f{size}};
		window.setSize(size);
		window.setView(view);
		interface.setSize(sf::Vector2f{size});
	}
}