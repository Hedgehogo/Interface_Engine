#include "KeyHandler.hpp"

#include "../../MouseWheel/MouseWheel.hpp"

namespace ie {
	auto KeyHandler::update() -> void {
		update_keyboard();
		update_mouse();
	}
	
	auto KeyHandler::update_keyboard() -> void {
		for(auto i{size_t{0}}; i < static_cast<size_t>(Key::MouseLeft); ++i) {
			keys_[i] = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i));
		}
	}
	
	auto KeyHandler::update_mouse() -> void {
		for(auto i{static_cast<size_t>(Key::MouseLeft)}; i < static_cast<size_t>(Key::MouseWheelUp); ++i) {
			keys_[i] = sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(i - static_cast<int>(Key::MouseLeft)));
		}
	}
	
	auto KeyHandler::get_key(Key key) const -> bool {
		if(key != Key::Unknown) {
			return keys_[static_cast<size_t>(key)];
		}
		return false;
	}
	
	auto KeyHandler::set_key(Key key, bool value) -> void {
		if(key != Key::Unknown) {
			keys_[static_cast<size_t>(key)] = value;
		}
	}
	
	auto KeyHandler::clear() -> void {
		keys_ = 0;
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
