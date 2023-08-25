#pragma once

#include "../IInteraction.hpp"

namespace ui {
	template<typename T = std::monostate>
	class IBasicMouseInteraction : public virtual IBaseInteraction {
	public:
		virtual BasicKeyEvent<T>& getLeftButtonEvent() = 0;
		
		virtual const BasicKeyEvent<T>& getLeftButtonEvent() const = 0;
		
		virtual BasicKeyEvent<T>& getRightButtonEvent() = 0;
		
		virtual const BasicKeyEvent<T>& getRightButtonEvent() const = 0;
		
		void update(sf::Vector2i mousePosition) override;
	};
	
	using IMouseInteraction = IBasicMouseInteraction<>;
}

#include "IBasicMouseInteraction.inl"
