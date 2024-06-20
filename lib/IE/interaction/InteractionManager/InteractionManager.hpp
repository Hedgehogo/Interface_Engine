#pragma once

#include "../IInteraction/IInteraction.hpp"
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
		
		auto get(size_t index) -> IInteraction&;
		
		auto add_interaction(IInteraction& interaction) -> void;
		
		auto delete_interaction(IInteraction& interaction) -> void;
		
		auto clear() -> void;
		
		auto is_blocked() const -> bool;
		
		auto handle_event(Event event) -> bool;
		
		auto update() -> void;
	
		virtual ~InteractionManager() = default;
		
	protected:
		std::vector<IInteraction*> interactions_;
		std::vector<IInteraction*> add_interactions_;
		std::vector<IInteraction*> delete_interactions_;
		bool block_;
	};
}