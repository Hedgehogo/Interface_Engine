#pragma once

namespace ie {
	class IUpdatable {
	public:
		virtual void update() = 0;
		
		virtual ~IUpdatable() = default;
	};
}
