#pragma once

#include "../IInteraction/IInteraction.hpp"
#include <algorithm>
#include <vector>

namespace ie {
	template<typename T>
	void ptr_sort(std::vector<T*>& vector) {
		std::sort(vector.begin(), vector.end(), [](T* first, T* second) {
			return *first < *second;
		});
	}
	
	class InteractionManager {
	public:
		explicit InteractionManager();
		
		size_t size();
		
		IInteraction& get(size_t index);
		
		void add_interaction(IInteraction& interaction);
		
		void delete_interaction(IInteraction& interaction);
		
		void clear();
		
		bool is_blocked() const;
		
		virtual void update(sf::Vector2i mouse_position);
	
		virtual ~InteractionManager() = default;
		
	protected:
		std::vector<IInteraction*> interactions_;
		std::vector<IInteraction*> add_interactions_;
		std::vector<IInteraction*> delete_interactions_;
		sf::Vector2i position_;
		bool block_;
	};
}