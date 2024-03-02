#pragma once

namespace ie {
	class IDrawable {
	public:
		virtual auto draw() -> void = 0;
		
		virtual ~IDrawable() = default;
	};
}
