#pragma once

#include "../iInteraction/iInteraction.hpp"
#include <algorithm>
#include <vector>

using ullint = unsigned long long;

namespace ui {
	template<typename T>
	void ptrSort(std::vector<T*>& vector) {
		std::sort(vector.begin(), vector.end(), [](T* first, T* second) {
			return *first < *second;
		});
	}
	
	class InteractionManager {
	public:
		explicit InteractionManager();
		
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