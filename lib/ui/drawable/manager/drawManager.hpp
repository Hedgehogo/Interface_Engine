#pragma once

#include <vector>
#include "../iDrawable/iDrawable.hpp"

namespace ui {
	class DrawManager : public IDrawable {
	public:
		DrawManager() = default;
		
		void add(IDrawable& drawable);
		
		void clear();
		
		void draw() override;
	
	protected:
		std::vector<IDrawable*> drawables;
	};
}
