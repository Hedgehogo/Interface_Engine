#pragma once

namespace ie {
	class IUpdatable {
	public:
		virtual auto update() -> void = 0;
		
		virtual ~IUpdatable() = default;
	};
}
