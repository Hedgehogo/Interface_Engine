#pragma once

#include "../IInteraction/IInteraction.hpp"
#include <algorithm>
#include <vector>

using ullint = unsigned long long;

namespace ie {
	template<typename T>
	void ptrSort(std::vector<T*>& vector) {
		std::sort(vector.begin(), vector.end(), [](T* first, T* second) {
			return *first < *second;
		});
	}
	
	class InteractionManager {
	public:
		explicit InteractionManager();
		
		std::size_t size();
		
		IInteraction& get(std::size_t index);
		
		void addInteraction(IInteraction& interaction);
		
		void deleteInteraction(IInteraction& interaction);
		
		void clear();
		
		bool isBlocked() const;
		
		virtual void update(sf::Vector2i mousePosition);
	
		virtual ~InteractionManager() = default;
		
	protected:
		std::vector<IInteraction*> interactions;
		std::vector<IInteraction*> addInteractions;
		std::vector<IInteraction*> deleteInteractions;
		sf::Vector2i position;
		bool block;
	};
}