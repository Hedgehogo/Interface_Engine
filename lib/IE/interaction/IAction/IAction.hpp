#pragma once

#include <box-ptr/BoxPtr.hpp>

namespace ie {
	using namespace bp;
	
	class IAction {
	public:
		virtual void start() {
		}
		
		virtual void finish() {
		}
		
		virtual ~IAction() = default;
	};
}
