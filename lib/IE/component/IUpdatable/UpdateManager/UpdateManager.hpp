#pragma once

#include <vector>
#include <cstddef>
#include "../IUpdatable/IUpdatable.hpp"

namespace ie {
	class UpdateManager : public virtual IUpdatable {
	public:
		UpdateManager() = default;
		
		auto size() -> size_t;
		
		auto get(size_t index) -> IUpdatable&;
		
		auto add(IUpdatable& updatable) -> void;
		
		auto clear() -> void;
		
		auto update() -> void override;
	
	protected:
		std::vector<IUpdatable*> updatable_;
	};
}
