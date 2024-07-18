#include "handle_event.hpp"

#include "../MouseWheel/MouseWheel.hpp"
#include "IE/event/EventHandler/KeyHandler/KeyHandler.hpp"

namespace ie {
	auto clear_event() -> void {
		MouseWheel::clear();
	}
}