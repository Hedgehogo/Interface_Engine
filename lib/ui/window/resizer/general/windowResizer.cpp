#include "windowResizer.hpp"

#include "../../window.hpp"

namespace ui {
	WindowResizer::WindowResizer(int internalBorderSize, int externalBorderSize, Key key) : internalBorderSize(internalBorderSize), externalBorderSize(externalBorderSize), key(key){
	}
	
	void swapBorders(int*& currentBorder, int& border, int& border2, int& grip, int& size){
		if (size < 0 && std::abs(size) > std::abs(grip)) {
			std::swap(border, border2);
			grip = -grip;
			size = -size;
			if(currentBorder == &border) {
				currentBorder = &border2;
			} else {
				currentBorder = &border;
			}
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
		
		swapBorders(currentBorder.y, borders.up, borders.down, grip.y, size.y);
		swapBorders(currentBorder.x, borders.left, borders.right, grip.x, size.x);
		
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
	
	void WindowResizer::getCurrentBorder(int& grip, int*& currentBorder, int& border, int& border2, int& windowSize, int& mousePosition) {
		if(mousePosition <= internalBorderSize && mousePosition >= -externalBorderSize) {
			currentBorder = &border;
			grip = mousePosition;
		} else if(windowSize - internalBorderSize <= mousePosition && windowSize + externalBorderSize >= mousePosition) {
			currentBorder = &border2;
			grip = mousePosition - windowSize;
		} else {
			currentBorder = nullptr;
			grip = 0;
		}
	};
	
	bool WindowResizer::update(sf::Vector2i mousePosition) {
		if(KeyHandler::isKeyPressed(key)) {
			if(currentBorder.x || currentBorder.y) {
				auto globalMousePosition = mousePosition + window->getPosition();
				if(currentBorder.y)
					(*currentBorder.y) = globalMousePosition.y - grip.y;
				if(currentBorder.x)
					(*currentBorder.x) = globalMousePosition.x - grip.x;
				
				setSize();
				return true;
				
			} else if (!oldKeyPressed) {
				sf::Vector2i windowSize{window->getSize()};
				setBorders();
				
				if(mousePosition.x >= -externalBorderSize && mousePosition.y >= -externalBorderSize && mousePosition.x <= windowSize.x + externalBorderSize && mousePosition.y <= windowSize.y + externalBorderSize) {
					getCurrentBorder(grip.y, currentBorder.y, borders.up, borders.down, windowSize.y, mousePosition.y);
					getCurrentBorder(grip.x, currentBorder.x, borders.left, borders.right, windowSize.x, mousePosition.x);
				}
				oldKeyPressed = true;
				return currentBorder.x || currentBorder.y;
			}
		} else {
			currentBorder = {};
			oldKeyPressed = false;
		}
		return false;
	}
}