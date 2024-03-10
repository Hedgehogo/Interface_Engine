#include "Key.hpp"

namespace ie {
	auto to_string(Key key) -> std::string {
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
			return "l-control";
		else if(key == Key::LShift)
			return "l-shift";
		else if(key == Key::LAlt)
			return "l-alt";
		else if(key == Key::LSystem)
			return "l-system";
		else if(key == Key::RControl)
			return "r-control";
		else if(key == Key::RShift)
			return "r-shift";
		else if(key == Key::RAlt)
			return "r-alt";
		else if(key == Key::RSystem)
			return "r-system";
		else if(key == Key::Menu)
			return "menu";
		else if(key == Key::LBracket)
			return "l-bracket";
		else if(key == Key::RBracket)
			return "r-bracket";
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
			return "page-up";
		else if(key == Key::PageDown)
			return "page-down";
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
			return "mouse-left";
		else if(key == Key::MouseRight)
			return "mouse-right";
		else if(key == Key::MouseMiddle)
			return "mouse-middle";
		else if(key == Key::MouseXButton1)
			return "mouse-x-button1";
		else if(key == Key::MouseXButton2)
			return "mouse-x-button2";
		
		else if(key == Key::MouseWheelUp)
			return "mouse-wheel-up";
		else if(key == Key::MouseWheelDown)
			return "mouse-wheel-down";
		else if(key == Key::MouseWheelLeft)
			return "mouse-wheel-left";
		else if(key == Key::MouseWheelRight)
			return "mouse-wheel-right";
		return "unknown";
	}
}

auto ieml::Decode<char, ie::Key>::decode(ieml::Node const& node) -> orl::Option<ie::Key> {
	auto& str{node.get_raw().except().str};
	if(str == "a")
		return ie::Key::A;
	else if(str == "b")
		return ie::Key::B;
	else if(str == "c")
		return ie::Key::C;
	else if(str == "d")
		return ie::Key::D;
	else if(str == "e")
		return ie::Key::E;
	else if(str == "f")
		return ie::Key::F;
	else if(str == "g")
		return ie::Key::G;
	else if(str == "h")
		return ie::Key::H;
	else if(str == "i")
		return ie::Key::I;
	else if(str == "j")
		return ie::Key::J;
	else if(str == "k")
		return ie::Key::K;
	else if(str == "l")
		return ie::Key::L;
	else if(str == "m")
		return ie::Key::M;
	else if(str == "n")
		return ie::Key::N;
	else if(str == "o")
		return ie::Key::O;
	else if(str == "p")
		return ie::Key::P;
	else if(str == "q")
		return ie::Key::Q;
	else if(str == "r")
		return ie::Key::R;
	else if(str == "s")
		return ie::Key::S;
	else if(str == "t")
		return ie::Key::T;
	else if(str == "u")
		return ie::Key::U;
	else if(str == "v")
		return ie::Key::V;
	else if(str == "w")
		return ie::Key::W;
	else if(str == "x")
		return ie::Key::X;
	else if(str == "y")
		return ie::Key::Y;
	else if(str == "z")
		return ie::Key::Z;
	else if(str == "num0")
		return ie::Key::Num0;
	else if(str == "num1")
		return ie::Key::Num1;
	else if(str == "num2")
		return ie::Key::Num2;
	else if(str == "num3")
		return ie::Key::Num3;
	else if(str == "num4")
		return ie::Key::Num4;
	else if(str == "num5")
		return ie::Key::Num5;
	else if(str == "num6")
		return ie::Key::Num6;
	else if(str == "num7")
		return ie::Key::Num7;
	else if(str == "num8")
		return ie::Key::Num8;
	else if(str == "num9")
		return ie::Key::Num9;
	else if(str == "escape")
		return ie::Key::Escape;
	else if(str == "l-control")
		return ie::Key::LControl;
	else if(str == "l-shift")
		return ie::Key::LShift;
	else if(str == "l-alt")
		return ie::Key::LAlt;
	else if(str == "l-system")
		return ie::Key::LSystem;
	else if(str == "r-control")
		return ie::Key::RControl;
	else if(str == "r-shift")
		return ie::Key::RShift;
	else if(str == "r-alt")
		return ie::Key::RAlt;
	else if(str == "r-system")
		return ie::Key::RSystem;
	else if(str == "menu")
		return ie::Key::Menu;
	else if(str == "l-bracket")
		return ie::Key::LBracket;
	else if(str == "r-bracket")
		return ie::Key::RBracket;
	else if(str == "semicolon")
		return ie::Key::Semicolon;
	else if(str == "comma")
		return ie::Key::Comma;
	else if(str == "period")
		return ie::Key::Period;
	else if(str == "quote")
		return ie::Key::Quote;
	else if(str == "slash")
		return ie::Key::Slash;
	else if(str == "backslash")
		return ie::Key::Backslash;
	else if(str == "tilde")
		return ie::Key::Tilde;
	else if(str == "equal")
		return ie::Key::Equal;
	else if(str == "hyphen")
		return ie::Key::Hyphen;
	else if(str == "space")
		return ie::Key::Space;
	else if(str == "enter")
		return ie::Key::Enter;
	else if(str == "backspace")
		return ie::Key::Backspace;
	else if(str == "tab")
		return ie::Key::Tab;
	else if(str == "page-up")
		return ie::Key::PageUp;
	else if(str == "page-down")
		return ie::Key::PageDown;
	else if(str == "end")
		return ie::Key::End;
	else if(str == "home")
		return ie::Key::Home;
	else if(str == "insert")
		return ie::Key::Insert;
	else if(str == "del")
		return ie::Key::Del;
	else if(str == "add")
		return ie::Key::Add;
	else if(str == "subtract")
		return ie::Key::Subtract;
	else if(str == "multiply")
		return ie::Key::Multiply;
	else if(str == "divide")
		return ie::Key::Divide;
	else if(str == "left")
		return ie::Key::Left;
	else if(str == "right")
		return ie::Key::Right;
	else if(str == "up")
		return ie::Key::Up;
	else if(str == "down")
		return ie::Key::Down;
	else if(str == "numpad0")
		return ie::Key::Numpad0;
	else if(str == "numpad1")
		return ie::Key::Numpad1;
	else if(str == "numpad2")
		return ie::Key::Numpad2;
	else if(str == "numpad3")
		return ie::Key::Numpad3;
	else if(str == "numpad4")
		return ie::Key::Numpad4;
	else if(str == "numpad5")
		return ie::Key::Numpad5;
	else if(str == "numpad6")
		return ie::Key::Numpad6;
	else if(str == "numpad7")
		return ie::Key::Numpad7;
	else if(str == "numpad8")
		return ie::Key::Numpad8;
	else if(str == "numpad9")
		return ie::Key::Numpad9;
	else if(str == "f1")
		return ie::Key::F1;
	else if(str == "f2")
		return ie::Key::F2;
	else if(str == "f3")
		return ie::Key::F3;
	else if(str == "f4")
		return ie::Key::F4;
	else if(str == "f5")
		return ie::Key::F5;
	else if(str == "f6")
		return ie::Key::F6;
	else if(str == "f7")
		return ie::Key::F7;
	else if(str == "f8")
		return ie::Key::F8;
	else if(str == "f9")
		return ie::Key::F9;
	else if(str == "f10")
		return ie::Key::F10;
	else if(str == "f11")
		return ie::Key::F11;
	else if(str == "f12")
		return ie::Key::F12;
	else if(str == "f13")
		return ie::Key::F13;
	else if(str == "f14")
		return ie::Key::F14;
	else if(str == "f15")
		return ie::Key::F15;
	else if(str == "pause")
		return ie::Key::Pause;
	else if(str == "mouse-left")
		return ie::Key::MouseLeft;
	else if(str == "mouse-right")
		return ie::Key::MouseRight;
	else if(str == "mouse-middle")
		return ie::Key::MouseMiddle;
	else if(str == "mouse-x-button1")
		return ie::Key::MouseXButton1;
	else if(str == "mouse-x-button2")
		return ie::Key::MouseXButton2;
	else if(str == "mouse-wheel-up")
		return ie::Key::MouseWheelUp;
	else if(str == "mouse-wheel-down")
		return ie::Key::MouseWheelDown;
	else if(str == "mouse-wheel-left")
		return ie::Key::MouseWheelLeft;
	else if(str == "mouse-wheel-right")
		return ie::Key::MouseWheelRight;
	else if(str == "unknown")
		return ie::Key::Unknown;
	return {};
}
