//
// Created by Professional on 04.07.2022.
//

#include "lambdaPositioning2.h"

namespace ui {
	LambdaPositioning2::LambdaPositioning2(sf::Vector2f (*findPosition)(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize, sf::Vector2f targetSize)) : positioning(findPosition), renderTarget(nullptr) {}
	
	void LambdaPositioning2::init(sf::RenderTarget &renderTarget) {
		this->renderTarget = &renderTarget;
	}
	
	sf::Vector2f LambdaPositioning2::findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) {
		sf::Vector2f targetSize{static_cast<sf::Vector2f>(renderTarget->getSize())};
		return positioning(parentPosition, parentSize, objectSize, targetSize);
	}
	
	void LambdaPositioning2::copy(LambdaPositioning2 *lambdaPositioning2) {
		lambdaPositioning2->renderTarget = this->renderTarget;
	}
	
	LambdaPositioning2 *LambdaPositioning2::copy() {
		LambdaPositioning2* lambdaPositioning2{new LambdaPositioning2{positioning}};
		LambdaPositioning2::copy(lambdaPositioning2);
		return lambdaPositioning2;
	}
}