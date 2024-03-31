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
	
	Window::Window(Interface&& interface, sf::WindowHandle handle, sf::ContextSettings&& settings) :
		window_(handle, settings), interface_(std::move(interface)), resizer_(get_window_resizer()) {
		construction();
		this->interface_.set_render_window_size(window_);
	}
	
	Window::Window(fs::path interface, sf::WindowHandle handle, sf::ContextSettings&& settings) :
		window_(handle, settings), interface_(make_interface(interface)), resizer_(get_window_resizer()) {
		construction();
		this->interface_.set_render_window_size(window_);
	}
	*/
	
	Window::Window(Interface::Make&& make, sf::String&& title, sf::VideoMode&& mode, sf::ContextSettings&& settings) :
		interface_(window_, dyn_buffer_, event_handler_.key_handler(), std::move(make.object)),
		resizer_(get_window_resizer()) {
		
		Window::re_calculate_min_size();
		auto size{sf::Vector2u{mode.width, mode.height}};
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
	
	auto Window::update(std::vector<Event> const& events) -> void {
		auto mouse_position{event_handler_.get_touch(std::numeric_limits<size_t>::max()).some_or({})};
		
		auto resizer_updated{resizer_->update(events, event_handler_)};
		
		window_.clear();
		interface_.update(sf::Vector2f{mouse_position}, !resizer_updated && window_.hasFocus());
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

	auto Window::set_position(sf::Vector2i const& position) -> void {
		event_handler_.move_window_position(window_.getPosition() - position);
		window_.setPosition(position);
	}
	
	auto Window::events() -> std::vector<Event> {
		ie::clear_event();
		event_handler_.update();
		
		auto result{std::vector<Event>{}};
		sf::Event event;
		while(window_.pollEvent(event)) {
			switch(event.type) {
				case sf::Event::Closed:
					window_.close();
					break;
				case sf::Event::LostFocus:
					result.emplace_back(Event::LostFocus({}));
					break;
				case sf::Event::GainedFocus:
					result.emplace_back(Event::GainedFocus({}));
					break;
				case sf::Event::TextEntered:
					result.emplace_back(Event::TextEntered(event.text.unicode));
					break;
				case sf::Event::KeyPressed:
					event_handler_.set_key(to_key(event.key.code), true);
					break;
				case sf::Event::KeyReleased:
					event_handler_.set_key(to_key(event.key.code), false);
					break;
				case sf::Event::MouseWheelScrolled: {
					MouseWheel::set_delta(event.mouseWheelScroll);
					event_handler_.set_scroll(event.mouseWheelScroll.wheel, event.mouseWheelScroll.delta);
				}
					break;
				case sf::Event::MouseButtonPressed:
					event_handler_.set_key(to_key(event.mouseButton.button), true);
					break;
				case sf::Event::MouseButtonReleased:
					event_handler_.set_key(to_key(event.mouseButton.button), false);
					break;
				case sf::Event::MouseMoved:
					event_handler_.set_touch(std::numeric_limits<size_t>::max(), {event.mouseMove.x, event.mouseMove.y});
					break;
				case sf::Event::JoystickButtonPressed:
					event_handler_.set_joystick_button(event.joystickButton.joystickId, event.joystickButton.button, true);
					break;
				case sf::Event::JoystickButtonReleased:
					event_handler_.set_joystick_button(event.joystickButton.joystickId, event.joystickButton.button, false);
					break;
				case sf::Event::JoystickMoved:
					result.emplace_back(Event::JoystickMove(event.joystickMove.joystickId, event.joystickMove.axis, event.joystickMove.position));
					break;
				case sf::Event::JoystickConnected:
					result.emplace_back(Event::JoystickConnect(event.joystickConnect.joystickId));
					break;
				case sf::Event::JoystickDisconnected:
					result.emplace_back(Event::JoystickDisconnect(event.joystickConnect.joystickId));
					break;
				case sf::Event::TouchBegan:
					event_handler_.set_touch(event.touch.finger, {event.touch.x, event.touch.y});
					break;
				case sf::Event::TouchMoved:
					event_handler_.set_touch(event.touch.finger, {event.touch.x, event.touch.y});
					break;
				case sf::Event::TouchEnded:
					event_handler_.remove_touch(event.touch.finger);
					break;
				case sf::Event::SensorChanged:
					break;
				default:
					break;
			}
		}
		
		event_handler_.poll_events(result);
		
		return result;
	}
	
	auto Window::handle_event(sf::Event event) -> void {
		if(event.type == sf::Event::MouseWheelScrolled) {
			MouseWheel::set_delta(event.mouseWheelScroll);
		}
		if(event.type == sf::Event::KeyPressed) {
			event_handler_.set_key(to_key(event.key.code), true);
		}
		if(event.type == sf::Event::KeyReleased) {
			event_handler_.set_key(to_key(event.key.code), false);
		}
		if(event.type == sf::Event::MouseButtonPressed) {
			event_handler_.set_key(to_key(event.mouseButton.button), true);
		}
		if(event.type == sf::Event::MouseButtonReleased) {
			event_handler_.set_key(to_key(event.mouseButton.button), false);
		}
	}
	
	auto make_window(fs::path file_path, sf::String&& title, sf::VideoMode&& mode, sf::ContextSettings&& settings) -> Window {
		return {make_interface(std::move(file_path)), std::move(title), std::move(mode), std::move(settings)};
	}
}