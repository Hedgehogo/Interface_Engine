#pragma once

#include <Box_Ptr/boxPtr.hpp>

using namespace bp;

namespace ie {
	class IAction {
	public:
		virtual void start() {
		}
		
		virtual void finish() {
		}
		
		virtual ~IAction() = default;
	};
}
