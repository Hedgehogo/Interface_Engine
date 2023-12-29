#include "Window.hpp"
#include "IE/sfml-events/handle_event/handle_event.hpp"

namespace ie {
	BaseWindowResizer* get_window_resizer() {
		return new WindowResizer{};
	}
	
	void Window::construction() {
		resizer->set_window(*this);
		interface.init(window);
		re_calculate_min_size();
		
		auto size{max(sf::Vector2u(min_size), window.getSize())};
		
		sf::View view{sf::Vector2f{size / 2u}, sf::Vector2f{size}};
		window.setView(view);
		interface.set_size(sf::Vector2f{size});
	}
	
	Window::Window(Interface&& interface) : interface(std::move(interface)), resizer(get_window_resizer()) {
		construction();
		this->interface.set_render_window_size(window);
	}
	
	Window::Window(Interface&& interface, const sf::String& title, const sf::VideoMode& mode, const sf::ContextSettings& settings) :
		window(
			(mode == sf::VideoMode{} ? [&] {
				auto new_window_size{interface.get_normal_size()};
				set_size({static_cast<unsigned>(std::ceil(new_window_size.x)), static_cast<unsigned>(std::ceil(new_window_size.y))});
				return sf::VideoMode{static_cast<unsigned>(std::ceil(new_window_size.x)), static_cast<unsigned>(std::ceil(new_window_size.y))};
			}() : mode), title, sf::Style::None, settings
		), interface(std::move(interface)), resizer(get_window_resizer()) {
		construction();
	}
	
	Window::Window(Interface&& interface, const sf::String& title, const sf::ContextSettings& settings) :
		window(
			[&] {
				auto new_window_size{interface.get_normal_size()};
				set_size({static_cast<unsigned>(std::ceil(new_window_size.x)), static_cast<unsigned>(std::ceil(new_window_size.y))});
				return sf::VideoMode{static_cast<unsigned>(std::ceil(new_window_size.x)), static_cast<unsigned>(std::ceil(new_window_size.y))};
			}(), title, sf::Style::None, settings
		), interface(std::move(interface)), resizer(get_window_resizer()) {
		construction();
	}
	
	Window::Window(Interface&& interface, sf::WindowHandle handle, const sf::ContextSettings& settings) :
		window(handle, settings), interface(std::move(interface)), resizer(get_window_resizer()) {
		construction();
		this->interface.set_render_window_size(window);
	}
	
	Window::Window(const std::filesystem::path& interface) : interface(make_interface(interface)), resizer(get_window_resizer()) {
		construction();
		this->interface.set_render_window_size(window);
	}
	
	Window::Window(const std::filesystem::path& interface, const sf::String& title, const sf::VideoMode& mode, const sf::ContextSettings& settings) :
		window(mode, title, sf::Style::None, settings), interface(make_interface(interface)), resizer(get_window_resizer()) {
		construction();
		this->interface.set_render_window_size(window);
	}
	
	Window::Window(const std::filesystem::path& interface, const sf::String& title, const sf::ContextSettings& settings) :
		window({1, 1}, title, sf::Style::None, settings), interface(make_interface(interface)), resizer(get_window_resizer()) {
		construction();
		this->interface.set_render_window_size(window);
	}
	
	Window::Window(const std::filesystem::path& interface, sf::WindowHandle handle, const sf::ContextSettings& settings) :
		window(handle, settings), interface(make_interface(interface)), resizer(get_window_resizer()) {
		construction();
		this->interface.set_render_window_size(window);
	}
	
	Window::Window(Interface::Make&& make, sf::String&& title, sf::VideoMode&& mode, sf::ContextSettings&& settings) :
		interface(window, std::move(make.object), std::move(make.animation_manager), std::move(make.interaction_stack)),
		resizer(get_window_resizer()) {
		
		Window::re_calculate_min_size();
		sf::Vector2u size{mode.width, mode.height};
		if(size == sf::Vector2u{0, 0}) {
			size = sf::Vector2u(map_vector2<float, std::ceil>(this->interface.get_normal_size()));
		}
		size = max(sf::Vector2u(min_size), size);
		
		window.create(sf::VideoMode{size.x, size.y}, title, sf::Style::None, settings);
		window.setView({sf::Vector2f{size / 2u}, sf::Vector2f{size}});
		interface.set_size(sf::Vector2f{size});
		resizer->set_window(*this);
	}
	
	void Window::create(sf::VideoMode mode, const sf::String& title, sf::Uint32, const sf::ContextSettings& settings) {
		window.create(mode, title, sf::Style::None, settings);
	}
	
	void Window::create(sf::VideoMode mode, const sf::String& title, const sf::ContextSettings& settings) {
		Window::create(mode, title, sf::Style::None, settings);
	}
	
	void Window::re_calculate_min_size() {
		min_size = max(sf::Vector2u{map_vector2<float, std::ceil>(this->interface.get_min_size())}, {1, 1});
	}
	
	void Window::update() {
		KeyHandler::update_mouse();
		sf::Vector2i mouse_position{sf::Mouse::getPosition(window)};
		
		bool resizer_updated = resizer->update(mouse_position);
		
		window.clear();
		interface.update(sf::Vector2f{(mouse_position)}, !resizer_updated && window.hasFocus());
		interface.draw();
		//interface.draw_debug(window, 0, 2, 90, 90);
		window.display();
		
		KeyHandler::clear_global_keys();
	}
	
	Interface& Window::get_interface() {
		return interface;
	}
	
	sf::RenderWindow& Window::get_window() {
		return window;
	}
	
	sf::Vector2u Window::get_min_size() const {
		return min_size;
	}
	
	void Window::set_size(const sf::Vector2u& size) {
		sf::View view{sf::Vector2f{size / 2u}, sf::Vector2f{size}};
		window.setSize(size);
		window.setView(view);
		interface.set_size(sf::Vector2f{size});
	}
}