#pragma once

#include "../../Modules/yaml-cpp/yaml.hpp"

namespace ie {
	enum class Key : int {
		unknown = -1,          ///< Unhandled key
		a = 0,                 ///< The A key
		b,                     ///< The B key
		c,                     ///< The C key
		d,                     ///< The D key
		e,                     ///< The E key
		f,                     ///< The F key
		g,                     ///< The G key
		h,                     ///< The H key
		i,                     ///< The I key
		j,                     ///< The J key
		k,                     ///< The K key
		l,                     ///< The L key
		m,                     ///< The M key
		n,                     ///< The N key
		o,                     ///< The O key
		p,                     ///< The P key
		q,                     ///< The Q key
		r,                     ///< The R key
		s,                     ///< The S key
		t,                     ///< The T key
		u,                     ///< The U key
		v,                     ///< The V key
		w,                     ///< The W key
		x,                     ///< The X key
		y,                     ///< The Y key
		z,                     ///< The Z key
		num0,                  ///< The 0 key
		num1,                  ///< The 1 key
		num2,                  ///< The 2 key
		num3,                  ///< The 3 key
		num4,                  ///< The 4 key
		num5,                  ///< The 5 key
		num6,                  ///< The 6 key
		num7,                  ///< The 7 key
		num8,                  ///< The 8 key
		num9,                  ///< The 9 key
		escape,                ///< The Escape key
		lControl,              ///< The left Control key
		lShift,                ///< The left Shift key
		lAlt,                  ///< The left Alt key
		lSystem,               ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
		rControl,              ///< The right Control key
		rShift,                ///< The right Shift key
		rAlt,                  ///< The right Alt key
		rSystem,               ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
		menu,                  ///< The Menu key
		lBracket,              ///< The [ key
		rBracket,              ///< The ] key
		semicolon,             ///< The ; key
		comma,                 ///< The , key
		period,                ///< The . key
		quote,                 ///< The ' key
		slash,                 ///< The / key
		backslash,             ///< The \ key
		tilde,                 ///< The ~ key
		equal,                 ///< The = key
		hyphen,                ///< The - key (hyphen)
		space,                 ///< The Space key
		enter,                 ///< The Enter/Return keys
		backspace,             ///< The Backspace key
		tab,                   ///< The Tabulation key
		pageUp,                ///< The Page up key
		pageDown,              ///< The Page down key
		end,                   ///< The End key
		home,                  ///< The Home key
		insert,                ///< The Insert key
		del,                   ///< The Delete key
		add,                   ///< The + key
		subtract,              ///< The - key (minus, usually from numpad)
		multiply,              ///< The * key
		divide,                ///< The / key
		left,                  ///< Left arrow
		right,                 ///< Right arrow
		up,                    ///< Up arrow
		down,                  ///< Down arrow
		numpad0,               ///< The numpad 0 key
		numpad1,               ///< The numpad 1 key
		numpad2,               ///< The numpad 2 key
		numpad3,               ///< The numpad 3 key
		numpad4,               ///< The numpad 4 key
		numpad5,               ///< The numpad 5 key
		numpad6,               ///< The numpad 6 key
		numpad7,               ///< The numpad 7 key
		numpad8,               ///< The numpad 8 key
		numpad9,               ///< The numpad 9 key
		f1,                    ///< The F1 key
		f2,                    ///< The F2 key
		f3,                    ///< The F3 key
		f4,                    ///< The F4 key
		f5,                    ///< The F5 key
		f6,                    ///< The F6 key
		f7,                    ///< The F7 key
		f8,                    ///< The F8 key
		f9,                    ///< The F9 key
		f10,                   ///< The F10 key
		f11,                   ///< The F11 key
		f12,                   ///< The F12 key
		f13,                   ///< The F13 key
		f14,                   ///< The F14 key
		f15,                   ///< The F15 key
		pause,                 ///< The Pause key
		
		dash = hyphen,    ///< \deprecated Use Hyphen instead
		backSpace = backspace, ///< \deprecated Use Backspace instead
		backSlash = backslash, ///< \deprecated Use Backslash instead
		semiColon = semicolon, ///< \deprecated Use Semicolon instead
		
		mouseLeft = 101,       ///< The left mouse button
		mouseRight,            ///< The right mouse button
		mouseMiddle,           ///< The middle (wheel) mouse button
		mouseXButton1,         ///< The first extra mouse button
		mouseXButton2,         ///< The second extra mouse button
		
		mouseWheelUp,          ///< The scroll the mouse wheel up
		mouseWheelDown,        ///< The scroll the mouse wheel down
		mouseWheelLeft,        ///< The scroll the mouse wheel left
		mouseWheelRight,       ///< The scroll the mouse wheel right
	};
	
	class KeyHandler {
	public:
		static std::vector<Key> getKeysPressed();
		
		static void setKeysPressed(std::vector<Key> keysPressed);
		
		static void update();
		
		static void updateKeyBoard();
		
		static void updateMouse();
		
		static void addKey(Key key);
		
		static void deleteKey(Key key);
		
		static void clear();
		
		static void clearGlobalKeys();
		
		static std::string toString(Key key);
		
		static bool isKeyPressed(Key key);
	
	protected:
		static std::vector<Key> keysPressed;
		static std::vector<Key> globalKeysPressed;
	};
	
	std::string toString(Key key);
	
	bool isKeyPressed(Key key);
	
	template<>
	struct Decode<Key> {
		static bool decode(const YAML::Node& node, Key& key);
	};
}