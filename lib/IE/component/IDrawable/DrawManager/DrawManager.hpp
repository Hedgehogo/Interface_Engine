#pragma once

#include <vector>
#include <cstddef>
#include "../IDrawable/IDrawable.hpp"

namespace ie {
	class DrawManager : public virtual IDrawable {
	public:
		DrawManager() = default;
		
		size_t size();
		
		IDrawable& get(size_t index);
		
		void add(IDrawable& drawable);
		
		void clear();
		
		void draw() override;
	
	protected:
		std::vector<IDrawable*> drawables;
	};
}