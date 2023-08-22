#include "LambdaPositioning2.hpp"

namespace ui {
	LambdaPositioning2::Make::Make(sf::Vector2f (* findPosition)(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f)) :
		findPosition(findPosition) {
	}
	
	LambdaPositioning2* LambdaPositioning2::Make::make(Positioning2InitInfo initInfo) {
		return new LambdaPositioning2{std::move(*this), initInfo};
	}
	
	LambdaPositioning2::LambdaPositioning2(LambdaPositioning2::Make&& make, Positioning2InitInfo initInfo) :
		positioning(make.findPosition), renderTarget(&initInfo.renderTarget) {
	}
	
	LambdaPositioning2::LambdaPositioning2(sf::Vector2f (* findPosition)(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f)) :
		positioning(findPosition), renderTarget(nullptr) {
	}
	
	void LambdaPositioning2::init(sf::RenderTarget& renderTarget) {
		this->renderTarget = &renderTarget;
	}
	
	sf::Vector2f LambdaPositioning2::findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) {
		sf::Vector2f targetSize{static_cast<sf::Vector2f>(renderTarget->getSize())};
		return positioning(parentPosition, parentSize, objectSize, targetSize);
	}
	
	LambdaPositioning2* LambdaPositioning2::copy() {
		return new LambdaPositioning2{*this};
	}
}