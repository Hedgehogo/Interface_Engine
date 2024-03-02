#include "IPositioning2.hpp"

namespace ie {
	auto IPositioning2::operator()(sf::Vector2f parent_position, sf::Vector2f parent_size, sf::Vector2f object_size) -> sf::Vector2f {
		return this->find_position(parent_position, parent_size, object_size);
	}

	/*Positioning *make_position(float coefficient, float offset, bool relative_target) {
		if(!relative_target) {
			return new InternalPositioning{coefficient, offset};
		}
		return new InternalTargetPositioning{coefficient, offset};
	}
	
	Positioning *make_position(float coefficient, float object_coefficient, float offset, bool relative_target) {
		if(!relative_target) {
			return new MatchPositioning{coefficient, object_coefficient, offset};
		}
		return new MatchTargetPositioning{coefficient, object_coefficient, offset};
	}*/
}