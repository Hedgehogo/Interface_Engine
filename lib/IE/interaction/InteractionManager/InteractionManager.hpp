#pragma once

#include "../IInteraction/IInteraction.hpp"
#include "../IInteraction/IPrioritisedInteraction/IPrioritisedInteraction.hpp"
#include <algorithm>
#include <vector>

namespace ie {
	template<typename T>
	auto ptr_sort(std::vector<T*>& vector) -> void {
		std::sort(vector.begin(), vector.end(), [](T* first, T* second) {
			return *first < *second;
		});
	}
	
	class InteractionManager {
	public:
		InteractionManager();
		
		auto size() -> size_t;
		
		auto add_prioritised(IPrioritisedInteraction& interaction) -> void;
		
		auto delete_prioritised(IPrioritisedInteraction& interaction) -> void;
		
		auto clear() -> void;
		
		auto is_blocked() const -> bool;
		
		auto handle_event(Event event) -> bool;
		
		virtual ~InteractionManager() = default;
		
	protected:
		std::vector<IPrioritisedInteraction*> interactions_;
	};
}