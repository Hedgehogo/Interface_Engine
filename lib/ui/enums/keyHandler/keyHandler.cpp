#include "keyHandler.hpp"

#include "../../sfmlEvents/mouseWheel/mouseWheel.hpp"

namespace ui {
	std::vector<Key> KeyHandler::keysPressed{};
	
	std::vector<Key> KeyHandler::getKeysPressed() {
		return keysPressed;
	}
	
	void KeyHandler::setKeysPressed(std::vector<Key> keysPressed) {
		KeyHandler::keysPressed = keysPressed;
	}
	
	void KeyHandler::addKey(Key key) {
		
		if(std::find(keysPressed.begin(), keysPressed.end(), key) == keysPressed.end()) {
			keysPressed.push_back(key);
		}
	}
	
	void KeyHandler::deleteKey(Key key) {
		auto element = std::find(keysPressed.begin(), keysPressed.end(), key);
		if(element != keysPressed.end()) {
			keysPressed.erase(element);
		}
	}
	
	void KeyHandler::clear() {
		keysPressed.clear();
	}
	
	std::string KeyHandler::toString(Key key) {
		if(key == Key::a)
			return "a";
		else if(key == Key::b)
			return "b";
		else if(key == Key::c)
			return "c";
		else if(key == Key::d)
			return "d";
		else if(key == Key::e)
			return "e";
		else if(key == Key::f)
			return "f";
		else if(key == Key::g)
			return "g";
		else if(key == Key::h)
			return "h";
		else if(key == Key::i)
			return "i";
		else if(key == Key::j)
			return "j";
		else if(key == Key::k)
			return "k";
		else if(key == Key::l)
			return "l";
		else if(key == Key::m)
			return "m";
		else if(key == Key::n)
			return "n";
		else if(key == Key::o)
			return "o";
		else if(key == Key::p)
			return "p";
		else if(key == Key::q)
			return "q";
		else if(key == Key::r)
			return "r";
		else if(key == Key::s)
			return "s";
		else if(key == Key::t)
			return "t";
		else if(key == Key::u)
			return "u";
		else if(key == Key::v)
			return "v";
		else if(key == Key::w)
			return "w";
		else if(key == Key::x)
			return "x";
		else if(key == Key::y)
			return "y";
		else if(key == Key::z)
			return "z";
		else if(key == Key::num0)
			return "num0";
		else if(key == Key::num1)
			return "num1";
		else if(key == Key::num2)
			return "num2";
		else if(key == Key::num3)
			return "num3";
		else if(key == Key::num4)
			return "num4";
		else if(key == Key::num5)
			return "num5";
		else if(key == Key::num6)
			return "num6";
		else if(key == Key::num7)
			return "num7";
		else if(key == Key::num8)
			return "num8";
		else if(key == Key::num9)
			return "num9";
		else if(key == Key::escape)
			return "escape";
		else if(key == Key::lControl)
			return "lControl";
		else if(key == Key::lShift)
			return "lShift";
		else if(key == Key::lAlt)
			return "lAlt";
		else if(key == Key::lSystem)
			return "lSystem";
		else if(key == Key::rControl)
			return "rControl";
		else if(key == Key::rShift)
			return "rShift";
		else if(key == Key::rAlt)
			return "rAlt";
		else if(key == Key::rSystem)
			return "rSystem";
		else if(key == Key::menu)
			return "menu";
		else if(key == Key::lBracket)
			return "lBracket";
		else if(key == Key::rBracket)
			return "rBracket";
		else if(key == Key::semicolon)
			return "semicolon";
		else if(key == Key::comma)
			return "comma";
		else if(key == Key::period)
			return "period";
		else if(key == Key::quote)
			return "quote";
		else if(key == Key::slash)
			return "slash";
		else if(key == Key::backslash)
			return "backslash";
		else if(key == Key::tilde)
			return "tilde";
		else if(key == Key::equal)
			return "equal";
		else if(key == Key::hyphen)
			return "hyphen";
		else if(key == Key::space)
			return "space";
		else if(key == Key::enter)
			return "enter";
		else if(key == Key::backspace)
			return "backspace";
		else if(key == Key::tab)
			return "tab";
		else if(key == Key::pageUp)
			return "pageUp";
		else if(key == Key::pageDown)
			return "pageDown";
		else if(key == Key::end)
			return "end";
		else if(key == Key::home)
			return "home";
		else if(key == Key::insert)
			return "insert";
		else if(key == Key::del)
			return "del";
		else if(key == Key::add)
			return "add";
		else if(key == Key::subtract)
			return "subtract";
		else if(key == Key::multiply)
			return "multiply";
		else if(key == Key::divide)
			return "divide";
		else if(key == Key::left)
			return "left";
		else if(key == Key::right)
			return "right";
		else if(key == Key::up)
			return "up";
		else if(key == Key::down)
			return "down";
		else if(key == Key::numpad0)
			return "numpad0";
		else if(key == Key::numpad1)
			return "numpad1";
		else if(key == Key::numpad2)
			return "numpad2";
		else if(key == Key::numpad3)
			return "numpad3";
		else if(key == Key::numpad4)
			return "numpad4";
		else if(key == Key::numpad5)
			return "numpad5";
		else if(key == Key::numpad6)
			return "numpad6";
		else if(key == Key::numpad7)
			return "numpad7";
		else if(key == Key::numpad8)
			return "numpad8";
		else if(key == Key::numpad9)
			return "numpad9";
		else if(key == Key::f1)
			return "f1";
		else if(key == Key::f2)
			return "f2";
		else if(key == Key::f3)
			return "f3";
		else if(key == Key::f4)
			return "f4";
		else if(key == Key::f5)
			return "f5";
		else if(key == Key::f6)
			return "f6";
		else if(key == Key::f7)
			return "f7";
		else if(key == Key::f8)
			return "f8";
		else if(key == Key::f9)
			return "f9";
		else if(key == Key::f10)
			return "f10";
		else if(key == Key::f11)
			return "f11";
		else if(key == Key::f12)
			return "f12";
		else if(key == Key::f13)
			return "f13";
		else if(key == Key::f14)
			return "f14";
		else if(key == Key::f15)
			return "f15";
		else if(key == Key::pause)
			return "pause";
		
		else if(key == Key::mouseLeft)
			return "mouseLeft";
		else if(key == Key::mouseRight)
			return "mouseRight";
		else if(key == Key::mouseMiddle)
			return "mouseMiddle";
		else if(key == Key::mouseXButton1)
			return "mouseXButton1";
		else if(key == Key::mouseXButton2)
			return "mouseXButton2";
		
		else if(key == Key::mouseWheelUp)
			return "mouseWheelUp";
		else if(key == Key::mouseWheelDown)
			return "mouseWheelDown";
		else if(key == Key::mouseWheelLeft)
			return "mouseWheelLeft";
		else if(key == Key::mouseWheelRight)
			return "mouseWheelRight";
		return "unknown";
	}
	
	bool KeyHandler::isKeyPressed(Key key) {
		
		if(std::find(keysPressed.begin(), keysPressed.end(), key) != keysPressed.end()) {
			return true;
		} else if(key <= Key::mouseWheelRight) {
			sf::Vector2f delta = MouseWheel::getDelta();
			switch(key) {
				case Key::mouseWheelUp:
					return delta.y > 0;
				case Key::mouseWheelDown:
					return delta.y < 0;
				case Key::mouseWheelRight:
					return delta.x > 0;
				case Key::mouseWheelLeft:
					return delta.x < 0;
			}
		}
		
		return false;
	}
	
	
	bool Decode<Key>::decode(const YAML::Node& node, Key& key) {
		std::string str = node.as<std::string>();
		if(str == "a")
			key = Key::a;
		else if(str == "b")
			key = Key::b;
		else if(str == "c")
			key = Key::c;
		else if(str == "d")
			key = Key::d;
		else if(str == "e")
			key = Key::e;
		else if(str == "f")
			key = Key::f;
		else if(str == "g")
			key = Key::g;
		else if(str == "h")
			key = Key::h;
		else if(str == "i")
			key = Key::i;
		else if(str == "j")
			key = Key::j;
		else if(str == "k")
			key = Key::k;
		else if(str == "l")
			key = Key::l;
		else if(str == "m")
			key = Key::m;
		else if(str == "n")
			key = Key::n;
		else if(str == "o")
			key = Key::o;
		else if(str == "p")
			key = Key::p;
		else if(str == "q")
			key = Key::q;
		else if(str == "r")
			key = Key::r;
		else if(str == "s")
			key = Key::s;
		else if(str == "t")
			key = Key::t;
		else if(str == "u")
			key = Key::u;
		else if(str == "v")
			key = Key::v;
		else if(str == "w")
			key = Key::w;
		else if(str == "x")
			key = Key::x;
		else if(str == "y")
			key = Key::y;
		else if(str == "z")
			key = Key::z;
		else if(str == "num0")
			key = Key::num0;
		else if(str == "num1")
			key = Key::num1;
		else if(str == "num2")
			key = Key::num2;
		else if(str == "num3")
			key = Key::num3;
		else if(str == "num4")
			key = Key::num4;
		else if(str == "num5")
			key = Key::num5;
		else if(str == "num6")
			key = Key::num6;
		else if(str == "num7")
			key = Key::num7;
		else if(str == "num8")
			key = Key::num8;
		else if(str == "num9")
			key = Key::num9;
		else if(str == "escape")
			key = Key::escape;
		else if(str == "l-control")
			key = Key::lControl;
		else if(str == "l-shift")
			key = Key::lShift;
		else if(str == "l-alt")
			key = Key::lAlt;
		else if(str == "l-system")
			key = Key::lSystem;
		else if(str == "r-control")
			key = Key::rControl;
		else if(str == "r-shift")
			key = Key::rShift;
		else if(str == "r-alt")
			key = Key::rAlt;
		else if(str == "r-system")
			key = Key::rSystem;
		else if(str == "menu")
			key = Key::menu;
		else if(str == "l-bracket")
			key = Key::lBracket;
		else if(str == "r-bracket")
			key = Key::rBracket;
		else if(str == "semicolon")
			key = Key::semicolon;
		else if(str == "comma")
			key = Key::comma;
		else if(str == "period")
			key = Key::period;
		else if(str == "quote")
			key = Key::quote;
		else if(str == "slash")
			key = Key::slash;
		else if(str == "backslash")
			key = Key::backslash;
		else if(str == "tilde")
			key = Key::tilde;
		else if(str == "equal")
			key = Key::equal;
		else if(str == "hyphen")
			key = Key::hyphen;
		else if(str == "space")
			key = Key::space;
		else if(str == "enter")
			key = Key::enter;
		else if(str == "backspace")
			key = Key::backspace;
		else if(str == "tab")
			key = Key::tab;
		else if(str == "page-up")
			key = Key::pageUp;
		else if(str == "page-down")
			key = Key::pageDown;
		else if(str == "end")
			key = Key::end;
		else if(str == "home")
			key = Key::home;
		else if(str == "insert")
			key = Key::insert;
		else if(str == "del")
			key = Key::del;
		else if(str == "add")
			key = Key::add;
		else if(str == "subtract")
			key = Key::subtract;
		else if(str == "multiply")
			key = Key::multiply;
		else if(str == "divide")
			key = Key::divide;
		else if(str == "left")
			key = Key::left;
		else if(str == "right")
			key = Key::right;
		else if(str == "up")
			key = Key::up;
		else if(str == "down")
			key = Key::down;
		else if(str == "numpad0")
			key = Key::numpad0;
		else if(str == "numpad1")
			key = Key::numpad1;
		else if(str == "numpad2")
			key = Key::numpad2;
		else if(str == "numpad3")
			key = Key::numpad3;
		else if(str == "numpad4")
			key = Key::numpad4;
		else if(str == "numpad5")
			key = Key::numpad5;
		else if(str == "numpad6")
			key = Key::numpad6;
		else if(str == "numpad7")
			key = Key::numpad7;
		else if(str == "numpad8")
			key = Key::numpad8;
		else if(str == "numpad9")
			key = Key::numpad9;
		else if(str == "f1")
			key = Key::f1;
		else if(str == "f2")
			key = Key::f2;
		else if(str == "f3")
			key = Key::f3;
		else if(str == "f4")
			key = Key::f4;
		else if(str == "f5")
			key = Key::f5;
		else if(str == "f6")
			key = Key::f6;
		else if(str == "f7")
			key = Key::f7;
		else if(str == "f8")
			key = Key::f8;
		else if(str == "f9")
			key = Key::f9;
		else if(str == "f10")
			key = Key::f10;
		else if(str == "f11")
			key = Key::f11;
		else if(str == "f12")
			key = Key::f12;
		else if(str == "f13")
			key = Key::f13;
		else if(str == "f14")
			key = Key::f14;
		else if(str == "f15")
			key = Key::f15;
		else if(str == "pause")
			key = Key::pause;
		else if(str == "dash")
			key = Key::dash;
		else if(str == "back-space")
			key = Key::backSpace;
		else if(str == "back-slash")
			key = Key::backSlash;
		else if(str == "semi-colon")
			key = Key::semiColon;
		else if(str == "mouse-left")
			key = Key::mouseLeft;
		else if(str == "mouse-right")
			key = Key::mouseRight;
		else if(str == "mouse-middle")
			key = Key::mouseMiddle;
		else if(str == "mouse-x-button1")
			key = Key::mouseXButton1;
		else if(str == "mouse-x-button2")
			key = Key::mouseXButton2;
		else if(str == "mouse-wheel-up")
			key = Key::mouseWheelUp;
		else if(str == "mouse-wheel-down")
			key = Key::mouseWheelDown;
		else if(str == "mouse-wheel-left")
			key = Key::mouseWheelLeft;
		else if(str == "mouse-wheel-right")
			key = Key::mouseWheelRight;
		else
			key = Key::unknown;
		return true;
	}
	
	std::string toString(Key key) {
		return KeyHandler::toString(key);
	}
	
	bool isKeyPressed(Key key) {
		return KeyHandler::isKeyPressed(key);
	}
	
	Key makeKeyFromYaml(YAML::Node node) {
		Key key;
		Decode<Key>::decode(node, key);
		return key;
	}
}