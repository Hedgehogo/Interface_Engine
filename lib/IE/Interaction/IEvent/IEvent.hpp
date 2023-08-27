#pragma once

#include <Box_Ptr/boxPtr.hpp>

using namespace bp;

namespace ie {
	class IEvent {
	public:
		virtual void start() {
		}
		
		virtual void finish() {
		}
		
		virtual ~IEvent() = default;
	};
}
