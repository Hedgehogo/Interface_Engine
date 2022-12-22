#pragma once

namespace ui {
	class IAnimatorUnit {
	public:
		virtual void restart() = 0;

		virtual IAnimatorUnit* update(float time) = 0;
		
		virtual ~IAnimatorUnit() = default; 
	};
} // ui