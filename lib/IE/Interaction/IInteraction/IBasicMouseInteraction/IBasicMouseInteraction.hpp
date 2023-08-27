#pragma once

#include "../IInteraction.hpp"

namespace ie {
	template<typename T = std::monostate>
	class IBasicMouseInteraction : public virtual IBaseInteraction {
	public:
		virtual BasicKeyAction<T>& getLeftButtonAction() = 0;
		
		virtual const BasicKeyAction<T>& getLeftButtonAction() const = 0;
		
		virtual BasicKeyAction<T>& getRightButtonAction() = 0;
		
		virtual const BasicKeyAction<T>& getRightButtonAction() const = 0;
		
		void update(sf::Vector2i mousePosition) override;
	};
	
	using IMouseInteraction = IBasicMouseInteraction<>;
}

#include "IBasicMouseInteraction.inl"
