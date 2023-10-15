#pragma once

#include <box-ptr/BoxPtr.hpp>

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
