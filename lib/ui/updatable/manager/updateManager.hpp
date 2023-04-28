#pragma once

#include <vector>
#include "../iUpdatable/iUpdatable.hpp"

namespace ui {
	class UpdateManager : public IUpdatable {
	protected:
		std::vector<IUpdatable*> updatables;
	
	public:
		UpdateManager() = default;
		
		void add(IUpdatable& updatable);
		
		void clear();
		
		void update() override;
	};
}
