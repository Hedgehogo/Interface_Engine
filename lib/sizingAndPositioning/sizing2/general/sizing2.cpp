#include "sizing2.h"

namespace ui {
	Sizing2::Sizing2(Sizing *horizontal, Sizing *vertical) :
		horizontal(horizontal), vertical(vertical), renderTarget(nullptr) {}
	
	Sizing2::Sizing2(bool relativeParent) :
		horizontal(createSize(relativeParent)), vertical(createSize(relativeParent)), renderTarget(nullptr) {}
	
	Sizing2::Sizing2(sf::Vector2f constSize) :
		horizontal(new ConstSizing{constSize.x}), vertical(new ConstSizing{constSize.y}), renderTarget(nullptr) {}
	
	Sizing2::Sizing2(sf::Vector2f coefficient, sf::Vector2f addition, bool relativeTarget) :
		horizontal(createSize(coefficient.x, addition.x, relativeTarget)),
		vertical(createSize(coefficient.y, addition.y, relativeTarget)),
		renderTarget(nullptr) {}
	
	Sizing2::Sizing2(sf::Vector2f targetCoefficient, sf::Vector2f parentCoefficient, sf::Vector2f addition) :
		horizontal(new SmartSizing{targetCoefficient.x, parentCoefficient.x, addition.x}),
		vertical(new SmartSizing{targetCoefficient.y, parentCoefficient.y, addition.y}),
		renderTarget(nullptr) {}
	
	Sizing2::~Sizing2() {
		delete horizontal;
		delete vertical;
	}
	
	void Sizing2::init(sf::RenderTarget &renderTarget, sf::Vector2f normalSize) {
		this->renderTarget = &renderTarget;
		horizontal->init(normalSize.x);
		vertical->init(normalSize.y);
	}
	
	sf::Vector2f Sizing2::findSize(sf::Vector2f parentSize) {
		sf::Vector2f targetSize{static_cast<sf::Vector2f>(renderTarget->getSize())};
		return {horizontal->findSize(parentSize.x, targetSize.x), vertical->findSize(parentSize.y, targetSize.y)};
	}
	
	sf::Vector2f Sizing2::getParentSize(sf::Vector2f objectSize) {
		return {horizontal->getParentSize(objectSize.x), vertical->getParentSize(objectSize.y)};
	}
	
	void Sizing2::copy(Sizing2 *sizing2) {
		sizing2->renderTarget = this->renderTarget;
	}
	
	Sizing2 *Sizing2::copy() {
		Sizing2* sizing2{new Sizing2{horizontal->copy(), vertical->copy()}};
		Sizing2::copy(sizing2);
		return sizing2;
	}
}