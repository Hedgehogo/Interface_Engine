#include "positioning2.hpp"
#include "../../positioning/make/makePositioning.hpp"

namespace ui {
	Positioning2::Positioning2(IPositioning* horizontal, IPositioning* vertical) :
		horizontal(horizontal), vertical(vertical), renderTarget(nullptr) {
	}
	
	Positioning2::Positioning2(sf::Vector2f coefficient, sf::Vector2f offset, bool relativeTarget) :
		horizontal(makePosition(coefficient.x, offset.x, relativeTarget)),
		vertical(makePosition(coefficient.y, offset.y, relativeTarget)),
		renderTarget(nullptr) {
	}
	
	Positioning2::Positioning2(Location2 parentLocation, Location2 objectLocation, sf::Vector2f offset) :
		horizontal(new MatchSidesPositioning{getHorizontalLocation(parentLocation), getHorizontalLocation(objectLocation), offset.x}),
		vertical(new MatchSidesPositioning{getVerticalLocation(parentLocation), getVerticalLocation(objectLocation), offset.y}),
		renderTarget(nullptr) {
	}
	
	Positioning2::Positioning2(sf::Vector2f coefficient, sf::Vector2f objectCoefficient, sf::Vector2f offset, bool relativeTarget) :
		horizontal(makePosition(coefficient.x, objectCoefficient.x, offset.x, relativeTarget)),
		vertical(makePosition(coefficient.y, objectCoefficient.y, offset.y, relativeTarget)),
		renderTarget(nullptr) {
	}
	
	Positioning2::~Positioning2() {
		delete horizontal;
		delete vertical;
	}
	
	void Positioning2::init(sf::RenderTarget& renderTarget) {
		this->renderTarget = &renderTarget;
	}
	
	sf::Vector2f Positioning2::findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) {
		sf::Vector2f targetSize{static_cast<sf::Vector2f>(renderTarget->getSize())};
		return {horizontal->findPosition(parentPosition.x, objectSize.x, parentSize.x, targetSize.x),
				vertical->findPosition(parentPosition.y, objectSize.y, parentSize.y, targetSize.y)};
	}
	
	void Positioning2::copy(Positioning2* positioning2) {
		positioning2->renderTarget = this->renderTarget;
	}
	
	Positioning2* Positioning2::copy() {
		Positioning2* positioning2{new Positioning2{horizontal->copy(), vertical->copy()}};
		Positioning2::copy(positioning2);
		return positioning2;
	}
	
	bool DecodePointer<Positioning2>::decodePointer(const YAML::Node& node, Positioning2*& positioning2) {
		if(node.IsScalar()) {
			positioning2 = new Positioning2{node.as<sf::Vector2f>()};
		} else {
			if(node["horizontal"] && node["vertical"]) {
				positioning2 = new Positioning2{
					node["horizontal"].as<IPositioning*>(),
					node["vertical"].as<IPositioning*>()
				};
			} else {
				auto offset{convDef(node["offset"], sf::Vector2f{})};
				
				if(node["coefficient"]) {
					positioning2 = new Positioning2{
						node["coefficient"].as<sf::Vector2f>(),
						offset,
						convBoolDef(node["relative"], "target", "parent")
					};
				} else if(node["object-coefficient"]) {
					auto objectCoefficient{node["object-coefficient"].as<sf::Vector2f>()};
					
					if(node["parent-coefficient"]) {
						positioning2 = new Positioning2{
							node["parent-coefficient"].as<sf::Vector2f>(),
							objectCoefficient, offset, false
						};
					} else if(node["target-coefficient"]) {
						positioning2 = new Positioning2{
							node["target-coefficient"].as<sf::Vector2f>(),
							objectCoefficient, offset, true
						};
					} else {
						throw YAML::BadConversion{node.Mark()};
					}
				} else if(node["parent-location"] && node["object-location"]) {
					positioning2 = new Positioning2{
						node["parent-location"].as<Location2>(),
						node["object-location"].as<Location2>(),
						offset
					};
				} else {
					throw YAML::BadConversion{node.Mark()};
				}
			}
		}
		return true;
	}
}