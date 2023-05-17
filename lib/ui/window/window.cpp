#include "window.hpp"
#include "ui/sfmlEvents/handleEvent/handleEvent.hpp"

namespace ui {
	IWindowResizer* getWindowResizer() {
		return new WindowResizer{};
	}
	
	void Window::construction() {
		resizer->setWindow(this);
		interface.init(*this);
		reCreateMinSize();
		
		auto size{sf::RenderWindow::getSize()};
		
		sf::View view{sf::Vector2f{size / 2u}, sf::Vector2f{size}};
		setView(view);
		interface.setSize(sf::Vector2f{size});
	}
	
	Window::Window(const Interface& interface) : resizer(getWindowResizer()), interface(interface) {
		this->interface.setRenderWindowSize(*this);
		construction();
	}
	
	Window::Window(const Interface& interface, const sf::String& title, const sf::VideoMode& mode, const sf::ContextSettings& settings) :
		RenderWindow((mode == sf::VideoMode{} ?
					  [&] {
						  auto newWindowSize{interface.getNormalSize()};
						  setSize({static_cast<unsigned>(std::ceil(newWindowSize.x)), static_cast<unsigned>(std::ceil(newWindowSize.y))});
						  return sf::VideoMode{static_cast<unsigned>(std::ceil(newWindowSize.x)), static_cast<unsigned>(std::ceil(newWindowSize.y))};
					  }() :
					  mode), title, sf::Style::None, settings), resizer(getWindowResizer()), interface(interface) {
		construction();
	}
	
	Window::Window(const Interface& interface, const sf::String& title, const sf::ContextSettings& settings) :
		RenderWindow([&] {
			auto newWindowSize{interface.getNormalSize()};
			setSize({static_cast<unsigned>(std::ceil(newWindowSize.x)), static_cast<unsigned>(std::ceil(newWindowSize.y))});
			return sf::VideoMode{static_cast<unsigned>(std::ceil(newWindowSize.x)), static_cast<unsigned>(std::ceil(newWindowSize.y))};
		}(), title, sf::Style::None, settings), resizer(getWindowResizer()), interface(interface) {
		construction();
	}
	
	Window::Window(const Interface& interface, sf::WindowHandle handle, const sf::ContextSettings& settings) : RenderWindow(handle, settings), resizer(getWindowResizer()), interface(interface) {
		this->interface.setRenderWindowSize(*this);
		construction();
	}
	
	Window::Window(const std::filesystem::path& interface) : interface(makeInterface(interface)), resizer(getWindowResizer()) {
		this->interface.setRenderWindowSize(*this);
		construction();
	}
	
	Window::Window(const std::filesystem::path& interface, const sf::String& title, const sf::VideoMode& mode, const sf::ContextSettings& settings) :
		RenderWindow(mode, title, sf::Style::None, settings), resizer(getWindowResizer()), interface(makeInterface(interface)) {
		this->interface.setRenderWindowSize(*this);
		construction();
	}
	
	Window::Window(const std::filesystem::path& interface, const sf::String& title, const sf::ContextSettings& settings) :
		RenderWindow({1, 1}, title, sf::Style::None, settings), resizer(getWindowResizer()), interface(makeInterface(interface)) {
		this->interface.setRenderWindowSize(*this);
		construction();
	}
	
	Window::Window(const std::filesystem::path& interface, sf::WindowHandle handle, const sf::ContextSettings& settings) : RenderWindow(handle, settings), interface(makeInterface(interface)) {
		this->interface.setRenderWindowSize(*this);
		construction();
	}
	
	void Window::create(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings) {
		Window::create(mode, title, sf::Style::None, settings);
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
		sf::Vector2i mousePosition{sf::Mouse::getPosition(*this)};
		
		bool resizerUpdated =  resizer->update(mousePosition);
		
		clear();
		interface.update(sf::Vector2f{(mousePosition)}, !resizerUpdated && hasFocus());
		interface.draw();
		//interface.drawDebug(window, 0, 2, 90, 90);
		display();
		
		KeyHandler::clearGlobalKeys();
	}
	
	Interface& Window::getInterface() {
		return interface;
	}
	
	const sf::Vector2f& Window::getMinSize() {
		return minSize;
	}
	
	void Window::setSize(const sf::Vector2u& size) {
		sf::RenderWindow::setSize(size);
		
		sf::View view{sf::Vector2f{size / 2u}, sf::Vector2f{size}};
		setView(view);
		interface.setSize(sf::Vector2f{size});
	}
}