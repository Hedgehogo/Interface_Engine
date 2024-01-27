#include "Window.hpp"
#include "IE/sfml-events/handle_event/handle_event.hpp"

namespace ie {
	BaseWindowResizer* get_window_resizer() {
		return new WindowResizer{};
	}
	
	void Window::construction() {
		resizer_->set_window(*this);
		interface_.init(window_);
		re_calculate_min_size();
		
		auto size{max(sf::Vector2u(min_size_), window_.getSize())};
		
		sf::View view{sf::Vector2f{size / 2u}, sf::Vector2f{size}};
		window_.setView(view);
		interface_.set_size(sf::Vector2f{size});
	}
	
	Window::Window(Interface&& interface) : interface_(std::move(interface)), resizer_(get_window_resizer()) {
		construction();
		this->interface_.set_render_window_size(window_);
	}
	
	Window::Window(Interface&& interface, const sf::String& title, const sf::VideoMode& mode, const sf::ContextSettings& settings) :
		window_(
			(mode == sf::VideoMode{} ? [&] {
				auto new_window_size{interface.get_normal_size()};
				set_size({static_cast<unsigned>(std::ceil(new_window_size.x)), static_cast<unsigned>(std::ceil(new_window_size.y))});
				return sf::VideoMode{static_cast<unsigned>(std::ceil(new_window_size.x)), static_cast<unsigned>(std::ceil(new_window_size.y))};
			}() : mode), title, sf::Style::None, settings
		), interface_(std::move(interface)), resizer_(get_window_resizer()) {
		construction();
	}
	
	Window::Window(Interface&& interface, const sf::String& title, const sf::ContextSettings& settings) :
		window_(
			[&] {
				auto new_window_size{interface.get_normal_size()};
				set_size({static_cast<unsigned>(std::ceil(new_window_size.x)), static_cast<unsigned>(std::ceil(new_window_size.y))});
				return sf::VideoMode{static_cast<unsigned>(std::ceil(new_window_size.x)), static_cast<unsigned>(std::ceil(new_window_size.y))};
			}(), title, sf::Style::None, settings
		), interface_(std::move(interface)), resizer_(get_window_resizer()) {
		construction();
	}
	
	Window::Window(Interface&& interface, sf::WindowHandle handle, const sf::ContextSettings& settings) :
		window_(handle, settings), interface_(std::move(interface)), resizer_(get_window_resizer()) {
		construction();
		this->interface_.set_render_window_size(window_);
	}
	
	/*old_yaml
	Window::Window(const std::filesystem::path& interface) : interface_(make_interface(interface)), resizer_(get_window_resizer()) {
		construction();
		this->interface_.set_render_window_size(window_);
	}
	
	Window::Window(const std::filesystem::path& interface, const sf::String& title, const sf::VideoMode& mode, const sf::ContextSettings& settings) :
		window_(mode, title, sf::Style::None, settings), interface_(make_interface(interface)), resizer_(get_window_resizer()) {
		construction();
		this->interface_.set_render_window_size(window_);
	}
	
	Window::Window(const std::filesystem::path& interface, const sf::String& title, const sf::ContextSettings& settings) :
		window_({1, 1}, title, sf::Style::None, settings), interface_(make_interface(interface)), resizer_(get_window_resizer()) {
		construction();
		this->interface_.set_render_window_size(window_);
	}
	
	Window::Window(const std::filesystem::path& interface, sf::WindowHandle handle, const sf::ContextSettings& settings) :
		window_(handle, settings), interface_(make_interface(interface)), resizer_(get_window_resizer()) {
		construction();
		this->interface_.set_render_window_size(window_);
	}
	*/
	
	Window::Window(Interface::Make&& make, sf::String&& title, sf::VideoMode&& mode, sf::ContextSettings&& settings) :
		interface_(window_, dyn_buffer, std::move(make.object), std::move(make.animation_manager), std::move(make.interaction_stack)),
		resizer_(get_window_resizer()) {
		
		Window::re_calculate_min_size();
		if(mode == sf::VideoMode{}) {
			sf::Vector2u normal_size{map_vector2<float, std::ceil>(this->interface_.get_normal_size())};
			sf::Vector2u size{max(sf::Vector2u(min_size_), normal_size)};
			mode = sf::VideoMode{size.x, size.y};
		}
		sf::Vector2u size{mode.width, mode.height};
		
		window_.create(mode, title, sf::Style::None, settings);
		window_.setView({sf::Vector2f{size / 2u}, sf::Vector2f{size}});
		interface_.set_size(sf::Vector2f{size});
		resizer_->set_window(*this);
	}
	
	void Window::create(sf::VideoMode mode, const sf::String& title, sf::Uint32, const sf::ContextSettings& settings) {
		window_.create(mode, title, sf::Style::None, settings);
	}
	
	void Window::create(sf::VideoMode mode, const sf::String& title, const sf::ContextSettings& settings) {
		Window::create(mode, title, sf::Style::None, settings);
	}
	
	void Window::re_calculate_min_size() {
		min_size_ = max(sf::Vector2u{map_vector2<float, std::ceil>(this->interface_.get_min_size())}, {1, 1});
	}
	
	void Window::update() {
		KeyHandler::update_mouse();
		sf::Vector2i mouse_position{sf::Mouse::getPosition(window_)};
		
		bool resizer_updated = resizer_->update(mouse_position);
		
		window_.clear();
		interface_.update(sf::Vector2f{(mouse_position)}, !resizer_updated && window_.hasFocus());
		interface_.draw();
		//interface.draw_debug(window, 0, 2, 90, 90);
		window_.display();
		
		KeyHandler::clear_global_keys();
	}
	
	Interface& Window::get_interface() {
		return interface_;
	}
	
	sf::RenderWindow& Window::get_window() {
		return window_;
	}
	
	sf::Vector2u Window::get_min_size() const {
		return min_size_;
	}
	
	void Window::set_size(const sf::Vector2u& size) {
		sf::View view{sf::Vector2f{size / 2u}, sf::Vector2f{size}};
		window_.setSize(size);
		window_.setView(view);
		interface_.set_size(sf::Vector2f{size});
	}
	
	Window make_window(fs::path file_path, sf::String&& title, sf::VideoMode&& mode, sf::ContextSettings&& settings) {
		return {make_interface(std::move(file_path)), std::move(title), std::move(mode), std::move(settings)};
	}
}