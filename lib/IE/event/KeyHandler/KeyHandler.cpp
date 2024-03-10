#include "KeyHandler.hpp"

#include "../../event/MouseWheel/MouseWheel.hpp"

namespace ie {
	std::vector<Key> KeyHandler::keys_pressed_{};
	std::vector<Key> KeyHandler::global_keys_pressed_{};
	
	auto KeyHandler::update() -> void {
		update_keyboard();
		update_mouse();
	}
	
	auto KeyHandler::update_keyboard() -> void {
		for(int i = 0; i < static_cast<int>(Key::MouseLeft); ++i) {
			if(sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i))) {
				if(std::find(keys_pressed_.begin(), keys_pressed_.end(), static_cast<Key>(i)) == keys_pressed_.end()) {
					global_keys_pressed_.push_back(static_cast<Key>(i));
				}
			}
		}
	}
	
	auto KeyHandler::update_mouse() -> void {
		for(int i = static_cast<int>(Key::MouseLeft); i < static_cast<int>(Key::MouseWheelUp); ++i) {
			if(sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(i - static_cast<int>(Key::MouseLeft)))) {
				if(std::find(keys_pressed_.begin(), keys_pressed_.end(), static_cast<Key>(i)) == keys_pressed_.end()) {
					global_keys_pressed_.push_back(static_cast<Key>(i));
				}
			}
		}
	}
	
	auto KeyHandler::add_key(Key key) -> void {
		if(std::find(keys_pressed_.begin(), keys_pressed_.end(), key) == keys_pressed_.end()) {
			keys_pressed_.push_back(key);
		}
	}
	
	auto KeyHandler::delete_key(Key key) -> void {
		auto element = std::find(keys_pressed_.begin(), keys_pressed_.end(), key);
		if(element != keys_pressed_.end()) {
			keys_pressed_.erase(element);
		}
	}
	
	auto KeyHandler::clear() -> void {
		keys_pressed_.clear();
	}
	
	auto KeyHandler::clear_global_keys() -> void {
		global_keys_pressed_.clear();
	}
	
	auto KeyHandler::is_key_pressed(Key key) -> bool {
		if(std::find(keys_pressed_.begin(), keys_pressed_.end(), key) != keys_pressed_.end()) {
			return true;
		} else if(std::find(global_keys_pressed_.begin(), global_keys_pressed_.end(), key) != global_keys_pressed_.end()) {
			return true;
		}
		sf::Vector2f delta = MouseWheel::get_delta();
		switch(key) {
			case Key::MouseWheelUp:
				return delta.y > 0;
			case Key::MouseWheelDown:
				return delta.y < 0;
			case Key::MouseWheelRight:
				return delta.x > 0;
			case Key::MouseWheelLeft:
				return delta.x < 0;
			default:
				return false;
		}
	}
	
	auto is_key_pressed(Key key) -> orl::Option<bool> {
		auto value{static_cast<int>(key)};
		if(value < static_cast<int>(Key::MouseLeft)) {
			return {sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(value))};
		} else if(value < static_cast<int>(Key::MouseWheelUp)) {
			auto button{static_cast<sf::Mouse::Button>(value - static_cast<int>(Key::MouseLeft))};
			return {sf::Mouse::isButtonPressed(button)};
		}
		return {};
	}
}
