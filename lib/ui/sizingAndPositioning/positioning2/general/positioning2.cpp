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
		return {horizontal->findPosition(parentPosition.x, objectSize.x, parentSize.x, targetSize.x),
				vertical->findPosition(parentPosition.y, objectSize.y, parentSize.y, targetSize.y)};
	}
	
	void Positioning2::copy(Positioning2 *positioning2) {
		positioning2->renderTarget = this->renderTarget;
	}
	
	Positioning2 *Positioning2::copy() {
		Positioning2* positioning2{new Positioning2{horizontal->copy(), vertical->copy()}};
		Positioning2::copy(positioning2);
		return positioning2;
	}
	
	Positioning2 *Positioning2::createFromYaml(const YAML::Node &node) {
		if(node["horizontal"] && node["vertical"]) {
			Positioning* horizontal;
			Positioning* vertical;
			
			node["horizontal"] >> horizontal;
			node["vertical"] >> vertical;
			
			return new Positioning2{horizontal, vertical};
		} else {
			sf::Vector2f offset{};
			
			if(node["offset"]) node["offset"] >> offset;
			
			if(node["coefficient"] || node["parent-coefficient"] || node["target-coefficient"]) {
				sf::Vector2f coefficient;
				bool relativeTarget{false};
				
				if(node["coefficient"]) {
					node["coefficient"] >> coefficient;
				} else if(node["parent-coefficient"]) {
					node["parent-coefficient"] >> coefficient;
				} else {
					node["target-coefficient"] >> coefficient;
					relativeTarget = true;
				}
				
				if(node["object-coefficient"]) {
					sf::Vector2f objectCoefficient;
					
					node["object-coefficient"] >> objectCoefficient;
					
					return new Positioning2{coefficient, objectCoefficient, offset, relativeTarget};
				} else {
					return new Positioning2{coefficient, offset, relativeTarget};
				}
			} else if(node["parent-location"] && node["object-location"]) {
				Location2 parentLocation{node["parent-location"].as<Location2>()};
				Location2 objectLocation{node["object-location"].as<Location2>()};
				
				return new Positioning2{parentLocation, objectLocation, offset};
			}
		}
		throw YAML::BadConversion{node.Mark()};
	}
}