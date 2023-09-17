#include "FnPositioning2.hpp"

namespace ie {
	FnPositioning2::Make::Make(FindPositionFn findPositionFn) :
		findPositionFn(std::move(findPositionFn)) {
	}
	
	FnPositioning2* FnPositioning2::Make::make(Positioning2InitInfo initInfo) {
		return new FnPositioning2{std::move(*this), initInfo};
	}
	
	FnPositioning2::FnPositioning2(Make&& make, Positioning2InitInfo initInfo) :
		findPositionFn(std::move(make.findPositionFn)), renderTarget(&initInfo.renderTarget) {
	}
	
	FnPositioning2::FnPositioning2(FindPositionFn findPositionFn) :
		findPositionFn(std::move(findPositionFn)), renderTarget(nullptr) {
	}
	
	void FnPositioning2::init(sf::RenderTarget& renderTarget) {
		this->renderTarget = &renderTarget;
	}
	
	sf::Vector2f FnPositioning2::findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) {
		sf::Vector2f targetSize{renderTarget->getSize()};
		return findPositionFn(parentPosition, parentSize, objectSize, targetSize);
	}
	
	FnPositioning2* FnPositioning2::copy() {
		return new FnPositioning2{*this};
	}
}