#include "basePositioning2.hpp"

namespace ui {
	sf::Vector2f BasePositioning2::operator()(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) {
		return this->findPosition(parentPosition, parentSize, objectSize);
	}
	
	BasePositioning2 *BasePositioning2::createFromYaml(const YAML::Node &node) {
		return nullptr;
	}
	
	Positioning *createPosition(float coefficient, float offset, bool relativeTarget) {
		if(!relativeTarget) {
			return new InternalPositioning{coefficient, offset};
		}
		return new InternalTargetPositioning{coefficient, offset};
	}
	
	Positioning *createPosition(float coefficient, float objectCoefficient, float offset, bool relativeTarget) {
		if(!relativeTarget) {
			return new MatchPositioning{coefficient, objectCoefficient, offset};
		}
		return new MatchTargetPositioning{coefficient, objectCoefficient, offset};
	}
}