#include "positioning2.h"

namespace ui {
	Positioning2::Positioning2(Positioning *horizontal, Positioning *vertical) :
		horizontal(horizontal), vertical(vertical) {}
	
	Positioning2::Positioning2(sf::Vector2f coefficient, sf::Vector2f offset) :
		horizontal(new InternalPositioning{coefficient.x, offset.x}),
		vertical(new InternalPositioning{coefficient.y, offset.y}) {}
	
	Positioning2::Positioning2(sf::Vector2f parentCoefficient, sf::Vector2f objectCoefficient, sf::Vector2f offset) :
		horizontal(new MatchPositioning{parentCoefficient.x, objectCoefficient.x, offset.x}),
		vertical(new MatchPositioning{parentCoefficient.y, objectCoefficient.y, offset.y}) {}
	
	Positioning2::Positioning2(Location2 parentLocation, Location2 objectLocation, sf::Vector2f offset) :
		horizontal(new MatchSidesPositioning{getHorizontalLocation(parentLocation), getHorizontalLocation(objectLocation), offset.x}),
		vertical(new MatchSidesPositioning{getVerticalLocation(parentLocation), getVerticalLocation(objectLocation), offset.y}){}
	
	Positioning2::~Positioning2() {
		delete horizontal;
		delete vertical;
	}
	
	void Positioning2::init(sf::RenderTarget &renderTarget) {
		horizontal->init(renderTarget);
		vertical->init(renderTarget);
	}
	
	sf::Vector2f Positioning2::findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) {
		return {horizontal->findPosition(parentPosition.x, parentSize.x, objectSize.x), vertical->findPosition(parentPosition.y, parentSize.y, objectSize.y)};
	}
	
	sf::Vector2f Positioning2::operator()(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) {
		return findPosition(parentPosition, parentSize, objectSize);
	}
	
	Positioning2 *Positioning2::copy() {
		return new Positioning2{horizontal->copy(), vertical->copy()};
	}
}