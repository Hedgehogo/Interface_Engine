#pragma once

#include <box-ptr/BoxPtr.hpp>

namespace ie {
	using namespace bp;
	
	class IAction {
	public:
		virtual auto start() -> void;
		
		virtual auto finish() -> void;
		
		virtual ~IAction() = default;
	};
}
