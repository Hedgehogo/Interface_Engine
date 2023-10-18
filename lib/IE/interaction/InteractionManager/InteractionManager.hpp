#pragma once

#include "../IInteraction/IInteraction.hpp"
#include <algorithm>
#include <vector>

using ullint = unsigned long long;

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
		
		std::size_t size();
		
		IInteraction& get(std::size_t index);
		
		void add_interaction(IInteraction& interaction);
		
		void delete_interaction(IInteraction& interaction);
		
		void clear();
		
		bool is_blocked() const;
		
		virtual void update(sf::Vector2i mouse_position);
	
		virtual ~InteractionManager() = default;
		
	protected:
		std::vector<IInteraction*> interactions;
		std::vector<IInteraction*> add_interactions;
		std::vector<IInteraction*> delete_interactions;
		sf::Vector2i position;
		bool block;
	};
}