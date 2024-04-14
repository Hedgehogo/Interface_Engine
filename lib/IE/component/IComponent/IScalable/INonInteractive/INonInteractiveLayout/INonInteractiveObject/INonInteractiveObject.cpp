#include "INonInteractiveObject.hpp"

namespace ie {
	auto INonInteractiveObject::handle_event(Event event) -> bool {
		return INonInteractive::handle_event(event);
	}
}
