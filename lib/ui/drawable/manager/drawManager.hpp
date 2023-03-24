#pragma once

#include <vector>
#include "../iDrawable/iDrawable.hpp"

namespace ui {
	class DrawManager : public IDrawable {
	protected:
		std::vector<IDrawable*> drawables;
		
	public:
		DrawManager() = default;
		
		void add(IDrawable &drawable);
		
		void clear();
		
		void draw() override;
	};
}
