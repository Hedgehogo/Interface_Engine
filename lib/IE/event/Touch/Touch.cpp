#include "Touch.hpp"

namespace ie {
	Touch::TouchMaker::TouchMaker(bool active) : active_(active) {
	}
	
	auto Touch::TouchMaker::operator()(event_system::Pointer pointer) -> Touch {
		return {pointer.position, !pointer.is_mouse() || active_};
	}
	
	auto Touch::from(bool active) -> Touch::TouchMaker {
		return TouchMaker{active};
	}
}