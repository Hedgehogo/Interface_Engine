#pragma once

#include "../iWindowResizer.hpp"
#include "ui/enums/keyHandler/keyHandler.hpp"
#include <variant>

namespace ui {
	class WindowResizer : public IWindowResizer {
	public:
		struct Borders {
			int up = 0, down = 0, left = 0, right = 0;
		};
	
	protected:
		virtual void setSize();
		
		virtual void setBorders();
		
		virtual void getCurrentBorder(int& grip, int*& currentBorder, int& border, int& border2, int& windowSize, int& mousePosition);
	
	public:
		WindowResizer(int internalBorderSize = 10, int externalBorderSize = 10, Key key = Key::mouseLeft);
		
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
