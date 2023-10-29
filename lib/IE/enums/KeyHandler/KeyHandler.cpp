#include "KeyHandler.hpp"

#include "../../sfml-events/MouseWheel/MouseWheel.hpp"

namespace ie {
	std::vector<Key> KeyHandler::keys_pressed_{};
	std::vector<Key> KeyHandler::global_keys_pressed_{};
	
	std::vector<Key> KeyHandler::get_keys_pressed() {
		return keys_pressed_;
	}
	
	void KeyHandler::set_keys_pressed(std::vector<Key> keys_pressed) {
		KeyHandler::keys_pressed_ = keys_pressed;
	}
	
	void KeyHandler::update() {
		update_key_board();
		update_mouse();
	}
	
	void KeyHandler::update_key_board() {
		for(int i = 0; i < static_cast<int>(Key::MouseLeft); ++i) {
			if(
				sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)) &&
					std::find(keys_pressed_.begin(), keys_pressed_.end(), static_cast<Key>(i)) == keys_pressed_.end()
				) {
				global_keys_pressed_.push_back(static_cast<Key>(i));
			}
		}
	}
	
	void KeyHandler::update_mouse() {
		for(int i = static_cast<int>(Key::MouseLeft); i < static_cast<int>(Key::MouseWheelUp); ++i) {
			if(
				sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(i - static_cast<int>(Key::MouseLeft))) &&
					std::find(keys_pressed_.begin(), keys_pressed_.end(), static_cast<Key>(i)) == keys_pressed_.end()
				) {
				global_keys_pressed_.push_back(static_cast<Key>(i));
			}
		}
	}
	
	void KeyHandler::add_key(Key key) {
		if(std::find(keys_pressed_.begin(), keys_pressed_.end(), key) == keys_pressed_.end()) {
			keys_pressed_.push_back(key);
		}
	}
	
	void KeyHandler::delete_key(Key key) {
		auto element = std::find(keys_pressed_.begin(), keys_pressed_.end(), key);
		if(element != keys_pressed_.end()) {
			keys_pressed_.erase(element);
		}
	}
	
	void KeyHandler::clear() {
		keys_pressed_.clear();
	}
	
	void KeyHandler::clear_global_keys() {
		global_keys_pressed_.clear();
	}
	
	bool KeyHandler::is_key_pressed(Key key) {
		if(
			std::find(keys_pressed_.begin(), keys_pressed_.end(), key) != keys_pressed_.end() ||
				std::find(global_keys_pressed_.begin(), global_keys_pressed_.end(), key) != global_keys_pressed_.end()
			) {
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
	
	std::string KeyHandler::to_string(Key key) {
		if(key == Key::A)
			return "a";
		else if(key == Key::B)
			return "b";
		else if(key == Key::C)
			return "c";
		else if(key == Key::D)
			return "d";
		else if(key == Key::E)
			return "e";
		else if(key == Key::F)
			return "f";
		else if(key == Key::G)
			return "g";
		else if(key == Key::H)
			return "h";
		else if(key == Key::I)
			return "i";
		else if(key == Key::J)
			return "j";
		else if(key == Key::K)
			return "k";
		else if(key == Key::L)
			return "l";
		else if(key == Key::M)
			return "m";
		else if(key == Key::N)
			return "n";
		else if(key == Key::O)
			return "o";
		else if(key == Key::P)
			return "p";
		else if(key == Key::Q)
			return "q";
		else if(key == Key::R)
			return "r";
		else if(key == Key::S)
			return "s";
		else if(key == Key::T)
			return "t";
		else if(key == Key::U)
			return "u";
		else if(key == Key::V)
			return "v";
		else if(key == Key::W)
			return "w";
		else if(key == Key::X)
			return "x";
		else if(key == Key::Y)
			return "y";
		else if(key == Key::Z)
			return "z";
		else if(key == Key::Num0)
			return "num0";
		else if(key == Key::Num1)
			return "num1";
		else if(key == Key::Num2)
			return "num2";
		else if(key == Key::Num3)
			return "num3";
		else if(key == Key::Num4)
			return "num4";
		else if(key == Key::Num5)
			return "num5";
		else if(key == Key::Num6)
			return "num6";
		else if(key == Key::Num7)
			return "num7";
		else if(key == Key::Num8)
			return "num8";
		else if(key == Key::Num9)
			return "num9";
		else if(key == Key::Escape)
			return "escape";
		else if(key == Key::LControl)
			return "lControl";
		else if(key == Key::LShift)
			return "lShift";
		else if(key == Key::LAlt)
			return "lAlt";
		else if(key == Key::LSystem)
			return "lSystem";
		else if(key == Key::RControl)
			return "rControl";
		else if(key == Key::RShift)
			return "rShift";
		else if(key == Key::RAlt)
			return "rAlt";
		else if(key == Key::RSystem)
			return "rSystem";
		else if(key == Key::Menu)
			return "menu";
		else if(key == Key::LBracket)
			return "lBracket";
		else if(key == Key::RBracket)
			return "rBracket";
		else if(key == Key::Semicolon)
			return "semicolon";
		else if(key == Key::Comma)
			return "comma";
		else if(key == Key::Period)
			return "period";
		else if(key == Key::Quote)
			return "quote";
		else if(key == Key::Slash)
			return "slash";
		else if(key == Key::Backslash)
			return "backslash";
		else if(key == Key::Tilde)
			return "tilde";
		else if(key == Key::Equal)
			return "equal";
		else if(key == Key::Hyphen)
			return "hyphen";
		else if(key == Key::Space)
			return "space";
		else if(key == Key::Enter)
			return "enter";
		else if(key == Key::Backspace)
			return "backspace";
		else if(key == Key::Tab)
			return "tab";
		else if(key == Key::PageUp)
			return "page_up";
		else if(key == Key::PageDown)
			return "page_down";
		else if(key == Key::End)
			return "end";
		else if(key == Key::Home)
			return "home";
		else if(key == Key::Insert)
			return "insert";
		else if(key == Key::Del)
			return "del";
		else if(key == Key::Add)
			return "add";
		else if(key == Key::Subtract)
			return "subtract";
		else if(key == Key::Multiply)
			return "multiply";
		else if(key == Key::Divide)
			return "divide";
		else if(key == Key::Left)
			return "left";
		else if(key == Key::Right)
			return "right";
		else if(key == Key::Up)
			return "up";
		else if(key == Key::Down)
			return "down";
		else if(key == Key::Numpad0)
			return "numpad0";
		else if(key == Key::Numpad1)
			return "numpad1";
		else if(key == Key::Numpad2)
			return "numpad2";
		else if(key == Key::Numpad3)
			return "numpad3";
		else if(key == Key::Numpad4)
			return "numpad4";
		else if(key == Key::Numpad5)
			return "numpad5";
		else if(key == Key::Numpad6)
			return "numpad6";
		else if(key == Key::Numpad7)
			return "numpad7";
		else if(key == Key::Numpad8)
			return "numpad8";
		else if(key == Key::Numpad9)
			return "numpad9";
		else if(key == Key::F1)
			return "f1";
		else if(key == Key::F2)
			return "f2";
		else if(key == Key::F3)
			return "f3";
		else if(key == Key::F4)
			return "f4";
		else if(key == Key::F5)
			return "f5";
		else if(key == Key::F6)
			return "f6";
		else if(key == Key::F7)
			return "f7";
		else if(key == Key::F8)
			return "f8";
		else if(key == Key::F9)
			return "f9";
		else if(key == Key::F10)
			return "f10";
		else if(key == Key::F11)
			return "f11";
		else if(key == Key::F12)
			return "f12";
		else if(key == Key::F13)
			return "f13";
		else if(key == Key::F14)
			return "f14";
		else if(key == Key::F15)
			return "f15";
		else if(key == Key::Pause)
			return "pause";
		
		else if(key == Key::MouseLeft)
			return "mouse_left";
		else if(key == Key::MouseRight)
			return "mouse_right";
		else if(key == Key::MouseMiddle)
			return "mouse_middle";
		else if(key == Key::MouseXButton1)
			return "mouse_x_button1";
		else if(key == Key::MouseXButton2)
			return "mouse_x_button2";
		
		else if(key == Key::MouseWheelUp)
			return "mouse_wheel_up";
		else if(key == Key::MouseWheelDown)
			return "mouse_wheel_down";
		else if(key == Key::MouseWheelLeft)
			return "mouse_wheel_left";
		else if(key == Key::MouseWheelRight)
			return "mouse_wheel_right";
		return "unknown";
	}
	
	/*old_yaml_decode_impl
	bool Decode<Key>::decode(const YAML::Node& node, Key& key) {
		std::string str = node.as<std::string>();
		if(str == "a")
			key = Key::A;
		else if(str == "b")
			key = Key::B;
		else if(str == "c")
			key = Key::C;
		else if(str == "d")
			key = Key::D;
		else if(str == "e")
			key = Key::E;
		else if(str == "f")
			key = Key::F;
		else if(str == "g")
			key = Key::G;
		else if(str == "h")
			key = Key::H;
		else if(str == "i")
			key = Key::I;
		else if(str == "j")
			key = Key::J;
		else if(str == "k")
			key = Key::K;
		else if(str == "l")
			key = Key::L;
		else if(str == "m")
			key = Key::M;
		else if(str == "n")
			key = Key::N;
		else if(str == "o")
			key = Key::O;
		else if(str == "p")
			key = Key::P;
		else if(str == "q")
			key = Key::Q;
		else if(str == "r")
			key = Key::R;
		else if(str == "s")
			key = Key::S;
		else if(str == "t")
			key = Key::T;
		else if(str == "u")
			key = Key::U;
		else if(str == "v")
			key = Key::V;
		else if(str == "w")
			key = Key::W;
		else if(str == "x")
			key = Key::X;
		else if(str == "y")
			key = Key::Y;
		else if(str == "z")
			key = Key::Z;
		else if(str == "num0")
			key = Key::Num0;
		else if(str == "num1")
			key = Key::Num1;
		else if(str == "num2")
			key = Key::Num2;
		else if(str == "num3")
			key = Key::Num3;
		else if(str == "num4")
			key = Key::Num4;
		else if(str == "num5")
			key = Key::Num5;
		else if(str == "num6")
			key = Key::Num6;
		else if(str == "num7")
			key = Key::Num7;
		else if(str == "num8")
			key = Key::Num8;
		else if(str == "num9")
			key = Key::Num9;
		else if(str == "escape")
			key = Key::Escape;
		else if(str == "l-control")
			key = Key::LControl;
		else if(str == "l-shift")
			key = Key::LShift;
		else if(str == "l-alt")
			key = Key::LAlt;
		else if(str == "l-system")
			key = Key::LSystem;
		else if(str == "r-control")
			key = Key::RControl;
		else if(str == "r-shift")
			key = Key::RShift;
		else if(str == "r-alt")
			key = Key::RAlt;
		else if(str == "r-system")
			key = Key::RSystem;
		else if(str == "menu")
			key = Key::Menu;
		else if(str == "l-bracket")
			key = Key::LBracket;
		else if(str == "r-bracket")
			key = Key::RBracket;
		else if(str == "semicolon")
			key = Key::Semicolon;
		else if(str == "comma")
			key = Key::Comma;
		else if(str == "period")
			key = Key::Period;
		else if(str == "quote")
			key = Key::Quote;
		else if(str == "slash")
			key = Key::Slash;
		else if(str == "backslash")
			key = Key::Backslash;
		else if(str == "tilde")
			key = Key::Tilde;
		else if(str == "equal")
			key = Key::Equal;
		else if(str == "hyphen")
			key = Key::Hyphen;
		else if(str == "space")
			key = Key::Space;
		else if(str == "enter")
			key = Key::Enter;
		else if(str == "backspace")
			key = Key::Backspace;
		else if(str == "tab")
			key = Key::Tab;
		else if(str == "page-up")
			key = Key::PageUp;
		else if(str == "page-down")
			key = Key::PageDown;
		else if(str == "end")
			key = Key::End;
		else if(str == "home")
			key = Key::Home;
		else if(str == "insert")
			key = Key::Insert;
		else if(str == "del")
			key = Key::Del;
		else if(str == "add")
			key = Key::Add;
		else if(str == "subtract")
			key = Key::Subtract;
		else if(str == "multiply")
			key = Key::Multiply;
		else if(str == "divide")
			key = Key::Divide;
		else if(str == "left")
			key = Key::Left;
		else if(str == "right")
			key = Key::Right;
		else if(str == "up")
			key = Key::Up;
		else if(str == "down")
			key = Key::Down;
		else if(str == "numpad0")
			key = Key::Numpad0;
		else if(str == "numpad1")
			key = Key::Numpad1;
		else if(str == "numpad2")
			key = Key::Numpad2;
		else if(str == "numpad3")
			key = Key::Numpad3;
		else if(str == "numpad4")
			key = Key::Numpad4;
		else if(str == "numpad5")
			key = Key::Numpad5;
		else if(str == "numpad6")
			key = Key::Numpad6;
		else if(str == "numpad7")
			key = Key::Numpad7;
		else if(str == "numpad8")
			key = Key::Numpad8;
		else if(str == "numpad9")
			key = Key::Numpad9;
		else if(str == "f1")
			key = Key::F1;
		else if(str == "f2")
			key = Key::F2;
		else if(str == "f3")
			key = Key::F3;
		else if(str == "f4")
			key = Key::F4;
		else if(str == "f5")
			key = Key::F5;
		else if(str == "f6")
			key = Key::F6;
		else if(str == "f7")
			key = Key::F7;
		else if(str == "f8")
			key = Key::F8;
		else if(str == "f9")
			key = Key::F9;
		else if(str == "f10")
			key = Key::F10;
		else if(str == "f11")
			key = Key::F11;
		else if(str == "f12")
			key = Key::F12;
		else if(str == "f13")
			key = Key::F13;
		else if(str == "f14")
			key = Key::F14;
		else if(str == "f15")
			key = Key::F15;
		else if(str == "pause")
			key = Key::Pause;
		else if(str == "dash")
			key = Key::Dash;
		else if(str == "back-space")
			key = Key::BackSpace;
		else if(str == "back-slash")
			key = Key::BackSlash;
		else if(str == "semi-colon")
			key = Key::SemiColon;
		else if(str == "mouse-left")
			key = Key::MouseLeft;
		else if(str == "mouse-right")
			key = Key::MouseRight;
		else if(str == "mouse-middle")
			key = Key::MouseMiddle;
		else if(str == "mouse-x-button1")
			key = Key::MouseXButton1;
		else if(str == "mouse-x-button2")
			key = Key::MouseXButton2;
		else if(str == "mouse-wheel-up")
			key = Key::MouseWheelUp;
		else if(str == "mouse-wheel-down")
			key = Key::MouseWheelDown;
		else if(str == "mouse-wheel-left")
			key = Key::MouseWheelLeft;
		else if(str == "mouse-wheel-right")
			key = Key::MouseWheelRight;
		else
			key = Key::Unknown;
		return true;

	}
	*/
	
	std::string to_string(Key key) {
		return KeyHandler::to_string(key);
	}
	
	bool is_key_pressed(Key key) {
		return KeyHandler::is_key_pressed(key);
	}
	
	/*old_yaml
	Key make_key_from_yaml(YAML::Node node) {
		Key key;
		Decode<Key>::decode(node, key);
		return key;
	}
	*/
}