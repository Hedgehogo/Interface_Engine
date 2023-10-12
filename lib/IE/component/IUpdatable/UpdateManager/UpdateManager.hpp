#pragma once

#include <vector>
#include "../IUpdatable/IUpdatable.hpp"

namespace ie {
	class UpdateManager : public virtual IUpdatable {
	public:
		UpdateManager() = default;
		
		std::size_t size();
		
		IUpdatable& get(std::size_t index);
		
		void add(IUpdatable& updatable);
		
		void clear();
		
		void update() override;
	
	protected:
		std::vector<IUpdatable*> updatable;
	};
}
