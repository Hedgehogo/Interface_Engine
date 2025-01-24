#pragma once

#include "../ITrigger/ITrigger.hpp"
#include "../ITrigger/IPrioritisedTrigger/IPrioritisedTrigger.hpp"
#include <algorithm>
#include <vector>

namespace ie {
	template<typename T>
	auto ptr_sort(std::vector<T*>& vector) -> void {
		std::sort(vector.begin(), vector.end(), [](T* first, T* second) {
			return *first < *second;
		});
	}
	
	class TriggerManager {
	public:
		TriggerManager();
		
		auto size() -> size_t;
		
		auto add_prioritised(IPrioritisedTrigger& trigger) -> void;
		
		auto delete_prioritised(IPrioritisedTrigger& trigger) -> void;
		
		auto clear() -> void;
		
		auto is_blocked() const -> bool;
		
		auto handle_event(Event event) -> bool;
		
		virtual ~TriggerManager() = default;
		
	protected:
		std::vector<IPrioritisedTrigger*> triggers_;
	};
}