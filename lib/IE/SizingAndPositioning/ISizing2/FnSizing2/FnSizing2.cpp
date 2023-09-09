#include "FnSizing2.hpp"

namespace ie {
	FnSizing2::Make::Make(FindSizeFn findSizeFn, GetParentSizeFn getParentSizeFn) :
		findSizeFn((findSizeFn)),
		getParentSizeFn((getParentSizeFn)) {
	}
	
	FnSizing2* FnSizing2::Make::make(Sizing2InitInfo initInfo) {
		return new FnSizing2{std::move(*this), initInfo};
	}
	
	FnSizing2::FnSizing2(Make&& make, Sizing2InitInfo initInfo) :
		findSizeFn(std::move(make.findSizeFn)),
		getParentSizeFn(std::move(make.getParentSizeFn)),
		renderTarget(&initInfo.renderTarget),
		normalSize(initInfo.normalSize) {
	}
	
	FnSizing2::FnSizing2(FindSizeFn findSizeFn, GetParentSizeFn getParentSizeFn) :
		findSizeFn(std::move(findSizeFn)), getParentSizeFn(std::move(getParentSizeFn)), renderTarget(nullptr), normalSize() {
	}
	
	void FnSizing2::init(sf::RenderTarget& renderTarget, sf::Vector2f normalSize) {
		this->renderTarget = &renderTarget;
		this->normalSize = normalSize;
	}
	
	sf::Vector2f FnSizing2::findSize(sf::Vector2f parentSize) {
		sf::Vector2f targetSize{renderTarget->getSize()};
		return findSizeFn(parentSize, targetSize, normalSize);
	}
	
	sf::Vector2f FnSizing2::getParentSize(sf::Vector2f objectSize) {
		return getParentSizeFn(objectSize);
	}
	
	FnSizing2* FnSizing2::copy() {
		return new FnSizing2{*this};
	}
}