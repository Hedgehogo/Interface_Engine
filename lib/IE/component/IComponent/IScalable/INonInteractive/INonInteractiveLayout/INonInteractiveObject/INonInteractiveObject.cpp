#include "INonInteractiveObject.hpp"

namespace ie {
	auto INonInteractiveObject::update_interactions(Event event) -> bool {
		return INonInteractive::update_interactions(event);
	}
}
