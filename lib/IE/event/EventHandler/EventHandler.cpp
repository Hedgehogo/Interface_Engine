#include "EventHandler.hpp"

namespace ie {
	auto EventHandler::key_handler() const -> KeyHandler const& {
		return key_handler_;
	}
	
	auto EventHandler::key_handler() -> KeyHandler& {
		return key_handler_;
	}
	
	auto EventHandler::get_key(Key key) const -> bool {
		return key_handler_.get_key(key);
	}
	
	auto EventHandler::set_key(Key key, bool value) -> void {
		key_handler_.set_key(key, value);
	}
	
	auto EventHandler::get_scroll() const -> sf::Vector2f {
		return {scroll_[0], scroll_[1]};
	}
	
	auto EventHandler::set_scroll(size_t id, float value) -> void {
		scroll_[id] = value;
	}
	
	auto EventHandler::get_pointer(size_t id) const -> orl::Option<sf::Vector2i> {
		if(auto iter{pointers_.find(id)}; iter != pointers_.end()) {
			return {iter->second};
		}
		return {};
	}
	
	auto EventHandler::set_pointer(size_t id, sf::Vector2i value) -> void {
		pointers_[id] = value;
	}
	
	auto EventHandler::remove_pointer(size_t id) -> void {
		pointers_.erase(id);
	}
	
	auto EventHandler::get_joystick_button(size_t id, size_t button_id) -> bool {
		return joystick_buttons_[id][button_id];
	}
	
	auto EventHandler::set_joystick_button(size_t id, size_t button_id, bool value) -> void {
		joystick_buttons_[id][button_id] = value;
	}
	
	auto EventHandler::move_window_position(sf::Vector2i position) -> void {
		for(auto& [id, pointer_position] : pointers_) {
			pointer_position += position;
		}
	}
	
	auto EventHandler::update() -> void {
		for(auto& item: scroll_) {
			item = 0.f;
		}
	}
	
	auto EventHandler::poll_events(std::vector<Event>& events) const -> void {
		for(auto i{size_t{0}}; i < scroll_.size(); ++i) {
			if(scroll_[i] )
			events.emplace_back(Event::Scroll(i, scroll_[i]));
		}
		for(auto [id, position]: pointers_) {
			events.emplace_back(Event::Pointer(id, position));
		}
		for(auto& [id, joystick]: joystick_buttons_) {
			for(auto [button_id, joystick_button]: joystick) {
				if(joystick_button) {
					events.emplace_back(Event::JoystickButton(id, button_id));
				}
			}
		}
	}
}
