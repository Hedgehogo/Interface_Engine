#pragma once

namespace ui {
	class IAnimationVariable {
	public:
		virtual void valueFromAnimation(float newValue) = 0;
	};
} // ui