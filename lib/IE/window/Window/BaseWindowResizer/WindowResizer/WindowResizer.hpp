#pragma once

#include "../BaseWindowResizer.hpp"
#include "IE/enums/KeyHandler/KeyHandler.hpp"
#include <variant>

namespace ie {
	class WindowResizer : public BaseWindowResizer {
	public:
		struct Borders {
			int up = 0, down = 0, left = 0, right = 0;
		};
	
	protected:
		virtual void setSize();
		
		virtual void setBorders();
		
		virtual void getCurrentBorder(int& grip, int*& currentBorder, int& border, int& border2, int& windowSize, int& mousePosition);
	
	public:
		WindowResizer(int internalBorderSize = 5, int externalBorderSize = 5, Key key = Key::MouseLeft);
		
		bool update(sf::Vector2i mousePosition) override;
	
	protected:
		int internalBorderSize;
		int externalBorderSize;
		Key key;
		
		Borders borders;
		sf::Vector2i grip;
		sf::Vector2<int*> currentBorder;
		bool oldKeyPressed;
	};
}