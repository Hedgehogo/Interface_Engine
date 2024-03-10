#include "Window.hpp"
#include "IE/event/handle_event/handle_event.hpp"

namespace ie {
	auto get_window_resizer() -> BaseWindowResizer* {
		return new WindowResizer{};
	}
	
	/*old_yaml
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
		interface_(window_, dyn_buffer_, key_handler_, std::move(make.object)),
		resizer_(get_window_resizer()) {
		
		Window::re_calculate_min_size();
		sf::Vector2u size{mode.width, mode.height};
		if(size == sf::Vector2u{0, 0}) {
			size = sf::Vector2u(map_vector2<float, std::ceil>(this->interface_.get_normal_size()));
		}
		size = max(sf::Vector2u(min_size_), size);

		window_.create(sf::VideoMode{size.x, size.y}, title, sf::Style::None, settings);
		window_.setView({sf::Vector2f{size / 2u}, sf::Vector2f{size}});
		interface_.set_size(sf::Vector2f{size});
		resizer_->set_window(*this);
	}
	
	auto Window::create(sf::VideoMode mode, sf::String const& title, sf::Uint32, sf::ContextSettings const& settings) -> void {
		window_.create(mode, title, sf::Style::None, settings);
	}
	
	auto Window::create(sf::VideoMode mode, sf::String const& title, sf::ContextSettings const& settings) -> void {
		Window::create(mode, title, sf::Style::None, settings);
	}
	
	auto Window::re_calculate_min_size() -> void {
		min_size_ = max(sf::Vector2u{map_vector2<float, std::ceil>(this->interface_.get_min_size())}, {1, 1});
	}
	
	auto Window::update() -> void {
		key_handler_.update_mouse();
		sf::Vector2i mouse_position{sf::Mouse::getPosition(window_)};
		
		bool resizer_updated = resizer_->update(mouse_position, key_handler_);
		
		window_.clear();
		interface_.update(sf::Vector2f{(mouse_position)}, !resizer_updated && window_.hasFocus());
		interface_.draw();
		//interface.draw_debug(window, 0, 2, 90, 90);
		window_.display();
	}
	
	auto Window::get_interface() -> Interface& {
		return interface_;
	}
	
	auto Window::get_window() -> sf::RenderWindow& {
		return window_;
	}
	
	auto Window::get_min_size() const -> sf::Vector2u {
		return min_size_;
	}
	
	auto Window::set_size(sf::Vector2u const& size) -> void {
		sf::View view{sf::Vector2f{size / 2u}, sf::Vector2f{size}};
		window_.setSize(size);
		window_.setView(view);
		interface_.set_size(sf::Vector2f{size});
	}
	
	auto Window::handle_event(sf::Event event) -> void {
		if(event.type == sf::Event::MouseWheelScrolled) {
			MouseWheel::set_delta(event.mouseWheelScroll);
		}
		if(event.type == sf::Event::KeyPressed) {
			key_handler_.add_key(static_cast<Key>(event.key.code));
		}
		if(event.type == sf::Event::KeyReleased) {
			key_handler_.delete_key(static_cast<Key>(event.key.code));
		}
		if(event.type == sf::Event::MouseButtonPressed) {
			key_handler_.add_key(static_cast<Key>(static_cast<int>(event.mouseButton.button) + static_cast<int>(Key::MouseLeft)));
		}
		if(event.type == sf::Event::MouseButtonReleased) {
			key_handler_.delete_key(static_cast<Key>(static_cast<int>(event.mouseButton.button) + static_cast<int>(Key::MouseLeft)));
		}
	}
	
	auto make_window(fs::path file_path, sf::String&& title, sf::VideoMode&& mode, sf::ContextSettings&& settings) -> Window {
		return {make_interface(std::move(file_path)), std::move(title), std::move(mode), std::move(settings)};
	}
}