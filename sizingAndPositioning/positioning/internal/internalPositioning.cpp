//
// Created by Professional on 30.06.2022.
//

#include "internalPositioning.h"

namespace ui {
	InternalPositioning::InternalPositioning(float coefficient, float offset) : coefficient(coefficient), offset(offset) {}
	
	void InternalPositioning::init(sf::RenderTarget &) {}
	
	float InternalPositioning::findPosition(float parentPosition, float parentSize, float objectSize) {
		return parentPosition + (parentSize - objectSize) * coefficient + offset;
	}
	
	InternalPositioning *InternalPositioning::copy() {
		return new InternalPositioning{coefficient, offset};
	}
	
	Positioning *createPosition(float coefficient, float offset) {
		return new InternalPositioning{coefficient, offset};
	}
}