#pragma once

#include <vector>
#include <cstddef>
#include "../IDrawable/IDrawable.hpp"

namespace ie {
	class DrawManager : public virtual IDrawable {
	public:
		DrawManager() = default;
		
		auto size() -> size_t;
		
		auto get(size_t index) -> IDrawable&;
		
		auto add(IDrawable& drawable) -> void;
		
		auto clear() -> void;
		
		auto draw() -> void override;
	
	protected:
		std::vector<IDrawable*> drawables_;
	};
}