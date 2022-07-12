#include "lambdaSizing2.h"

namespace ui {
	LambdaSizing2::LambdaSizing2(sf::Vector2f (*findSize)(sf::Vector2f parentSize, sf::Vector2f targetSize, sf::Vector2f normalSize), sf::Vector2f (*getParentMinSize)(sf::Vector2f objectMinSize)) :
		sizing(findSize), minSize(getParentMinSize), renderTarget(nullptr), normalSize() {}
	
	void LambdaSizing2::init(sf::RenderTarget &renderTarget, sf::Vector2f normalSize) {
		this->renderTarget = &renderTarget;
		this->normalSize = normalSize;
	}
	
	sf::Vector2f LambdaSizing2::findSize(sf::Vector2f parentSize) {
		sf::Vector2f targetSize{static_cast<sf::Vector2f>(renderTarget->getSize())};
		return sizing(parentSize, targetSize, normalSize);
	}
	
	sf::Vector2f LambdaSizing2::getParentMinSize(sf::Vector2f objectMinSize) {
		return minSize(objectMinSize);
	}
	
	void LambdaSizing2::copy(LambdaSizing2 *sizing2) {
		sizing2->renderTarget = this->renderTarget;
		sizing2->normalSize = this->normalSize;
	}
	
	LambdaSizing2 *LambdaSizing2::copy() {
		LambdaSizing2* lambdaSizing2{new LambdaSizing2{sizing, minSize}};
		LambdaSizing2::copy(lambdaSizing2);
		return lambdaSizing2;
	}
}