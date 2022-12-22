#pragma once

#include <type_traits>

namespace ui {
	class BaseChangeVariable {
	public:
		virtual float getSize() = 0;

		virtual float operator()(float frame) = 0;
	};
}