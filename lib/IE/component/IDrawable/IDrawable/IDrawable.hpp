#pragma once

namespace ie {
	class IDrawable {
	public:
		virtual void draw() = 0;
		
		virtual ~IDrawable() = default;
	};
}
