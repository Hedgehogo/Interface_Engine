#include "lambdaSizing2.hpp"

namespace ui {
	LambdaSizing2::LambdaSizing2(sf::Vector2f (* findSize)(sf::Vector2f parentSize, sf::Vector2f targetSize, sf::Vector2f normalSize), sf::Vector2f (* getParentMinSize)(sf::Vector2f objectMinSize)) :
		sizing(findSize), minSize(getParentMinSize), renderTarget(nullptr), normalSize() {
	}
	
	void LambdaSizing2::init(sf::RenderTarget& renderTarget, sf::Vector2f normalSize) {
		this->renderTarget = &renderTarget;
		this->normalSize = normalSize;
	}
	
	sf::Vector2f LambdaSizing2::findSize(sf::Vector2f parentSize) {
		sf::Vector2f targetSize{static_cast<sf::Vector2f>(renderTarget->getSize())};
		return sizing(parentSize, targetSize, normalSize);
	}
	
	sf::Vector2f LambdaSizing2::getParentSize(sf::Vector2f objectSize) {
		return minSize(objectSize);
	}
	
	LambdaSizing2* LambdaSizing2::copy() {
		return new LambdaSizing2{*this};
	}
}