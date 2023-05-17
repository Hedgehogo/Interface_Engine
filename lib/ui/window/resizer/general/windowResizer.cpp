#include "windowResizer.hpp"

#include "../../window.hpp"

namespace ui {
	WindowResizer::WindowResizer(unsigned int borderSize, Key key) : borderSize(borderSize), key(key){
	}
	
	void swapBorders(int*& currentBorder, int& border, int& border2, int& grip, int& size){
		std::swap(border, border2);
		grip = -grip;
		size = -size;
		if (currentBorder == &border){
			currentBorder = &border2;
		} else {
			currentBorder = &border;
		}
	}
	
	void checkMinSize(int& size, float& minSize, int*& currentBorder, int& border, int& border2){
		if (size < minSize){
			if (currentBorder == &border){
				border = border2 - minSize;
			} else {
				border2 = border + minSize;
			}
		}
	}
	
	void WindowResizer::setSize() {
		sf::Vector2i size{borders.right - borders.left, borders.down - borders.up};
		
		if (size.y < 0) {
			swapBorders(currentBorder.y, borders.up, borders.down, grip.y, size.y);
		}
		
		if (size.x < 0) {
			swapBorders(currentBorder.x, borders.left, borders.right, grip.x, size.x);
		}
		
		auto minSize{window->getMinSize()};
		
		checkMinSize(size.y, minSize.y, currentBorder.y, borders.up, borders.down);
		checkMinSize(size.x, minSize.x, currentBorder.x, borders.left, borders.right);
		
		window->setPosition({borders.left, borders.up});
		window->setSize({static_cast<unsigned>(borders.right - borders.left), static_cast<unsigned>(borders.down - borders.up)});
		
	}
	
	void WindowResizer::setBorders() {
		sf::Vector2i windowPosition{window->getPosition()};
		sf::Vector2u windowSize{window->getSize()};
		borders = {
			windowPosition.y,
			windowPosition.y + static_cast<int>(windowSize.y),
			windowPosition.x,
			windowPosition.x + static_cast<int>(windowSize.x)
		};
	}
	
	void WindowResizer::getCurrentBorder(int& grip, int*& currentBorder, int& border, int& border2,  unsigned& windowSize, int& mousePosition, int& absMousePosition) {
		if(absMousePosition <= borderSize) {
			currentBorder = &border;
			grip = mousePosition;
		} else if(windowSize - borderSize <= mousePosition && windowSize + borderSize >= mousePosition) {
			currentBorder = &border2;
			grip = mousePosition - windowSize;
		} else {
			currentBorder = nullptr;
			grip = 0;
		}
	};
	
	bool WindowResizer::update(sf::Vector2i mousePosition) {
		if(KeyHandler::isKeyPressed(key)) {
			auto globalMousePosition = mousePosition + window->getPosition();
			if(currentBorder.x || currentBorder.y) {
				if(currentBorder.y)
					(*currentBorder.y) = globalMousePosition.y - grip.y;
				if(currentBorder.x)
					(*currentBorder.x) = globalMousePosition.x - grip.x;
				
				setSize();
				return true;
				
			} else if (!oldKeyPressed) {
				sf::Vector2u windowSize{window->getSize()};
				sf::Vector2i windowPosition{window->getPosition()};
				sf::Vector2i absMousePosition{std::abs(globalMousePosition.x - windowPosition.x), std::abs(globalMousePosition.y - windowPosition.y)};
				
				setBorders();
				
				getCurrentBorder(grip.y, currentBorder.y, borders.up,   borders.down,  windowSize.y, mousePosition.y, absMousePosition.y);
				getCurrentBorder(grip.x, currentBorder.x, borders.left, borders.right, windowSize.x, mousePosition.x, absMousePosition.x);
				
				return currentBorder.x || currentBorder.y;
			}
			oldKeyPressed = true;
		} else {
			currentBorder = {};
			oldKeyPressed = false;
		}
		return false;
	}
}