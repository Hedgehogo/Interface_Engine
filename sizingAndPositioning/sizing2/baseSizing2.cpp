#include "baseSizing2.h"

namespace ui {
	sf::Vector2f BaseSizing2::operator()(sf::Vector2f parentSize) {
		return this->findSize(parentSize);
	}
	
	Sizing *createSize(float coefficient, float addition, bool relativeTarget) {
		if(!relativeTarget) {
			return new ParentCoefficientSizing{coefficient, addition};
		}
		return new TargetCoefficientSizing{coefficient, addition};
	}
}