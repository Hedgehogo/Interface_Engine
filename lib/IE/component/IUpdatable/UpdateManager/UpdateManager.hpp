#pragma once

#include <vector>
#include <cstddef>
#include "../IUpdatable/IUpdatable.hpp"

namespace ie {
	class UpdateManager : public virtual IUpdatable {
	public:
		UpdateManager() = default;
		
		size_t size();
		
		IUpdatable& get(size_t index);
		
		void add(IUpdatable& updatable);
		
		void clear();
		
		void update() override;
	
	protected:
		std::vector<IUpdatable*> updatable_;
	};
}
