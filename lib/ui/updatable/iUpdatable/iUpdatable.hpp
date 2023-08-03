#pragma once

namespace ui {
	class IUpdatable {
	public:
		virtual void update() = 0;
		
		virtual ~IUpdatable() = default;
	};
}
