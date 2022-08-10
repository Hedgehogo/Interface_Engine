#include "positioning2.hpp"

namespace ui {
	Positioning2::Positioning2(Positioning *horizontal, Positioning *vertical) :
		horizontal(horizontal), vertical(vertical), renderTarget(nullptr) {}
	
	Positioning2::Positioning2(sf::Vector2f coefficient, sf::Vector2f offset, bool relativeTarget) :
		horizontal(createPosition(coefficient.x, offset.x, relativeTarget)),
		vertical(createPosition(coefficient.y, offset.y, relativeTarget)),
		renderTarget(nullptr) {}
	
	Positioning2::Positioning2(Location2 parentLocation, Location2 objectLocation, sf::Vector2f offset) :
		horizontal(new MatchSidesPositioning{getHorizontalLocation(parentLocation), getHorizontalLocation(objectLocation), offset.x}),
		vertical(new MatchSidesPositioning{getVerticalLocation(parentLocation), getVerticalLocation(objectLocation), offset.y}),
		renderTarget(nullptr) {}
	
	Positioning2::Positioning2(sf::Vector2f coefficient, sf::Vector2f objectCoefficient, sf::Vector2f offset, bool relativeTarget) :
		horizontal(createPosition(coefficient.x, objectCoefficient.x, offset.x, relativeTarget)),
		vertical(createPosition(coefficient.y, objectCoefficient.y, offset.y, relativeTarget)),
		renderTarget(nullptr) {}
	
	Positioning2::~Positioning2() {
		delete horizontal;
		delete vertical;
	}
	
	void Positioning2::init(sf::RenderTarget &renderTarget) {
		this->renderTarget = &renderTarget;
	}
	
	sf::Vector2f Positioning2::findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) {
		sf::Vector2f targetSize{static_cast<sf::Vector2f>(renderTarget->getSize())};
		return {horizontal->findPosition(parentPosition.x, objectSize.x, parentSize.x, targetSize.x), vertical->findPosition(parentPosition.y, objectSize.y, parentSize.y, targetSize.y)};
	}
	
	void Positioning2::copy(Positioning2 *positioning2) {
		positioning2->renderTarget = this->renderTarget;
	}
	
	Positioning2 *Positioning2::copy() {
		Positioning2* positioning2{new Positioning2{horizontal->copy(), vertical->copy()}};
		Positioning2::copy(positioning2);
		return positioning2;
	}
}