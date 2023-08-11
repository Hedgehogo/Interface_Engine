#pragma once

#include <vector>
#include "../iDrawable/iDrawable.hpp"

namespace ui {
	class DrawManager : public IDrawable {
	public:
		DrawManager() = default;
		
		std::size_t size();
		
		IDrawable& get(std::size_t index);
		
		void add(IDrawable& drawable);
		
		void clear();
		
		void draw() override;
	
	protected:
		std::vector<IDrawable*> drawables;
	};
}
