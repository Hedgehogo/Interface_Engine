#pragma once

#include "../IInteraction.hpp"

namespace ie {
	template<typename T>
	class IBasicMouseInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct IBasicMouseInteraction : public virtual IBasicInteraction<T> {
			ie::IBasicMouseInteraction<T>* make(BasicActionInitInfo<T> initInfo) override = 0;
		};
	}
	
	template<typename T = std::monostate>
	class IBasicMouseInteraction : public virtual IBasicInteraction<T> {
	public:
		using Make = make_system::IBasicMouseInteraction<T>;
		
		virtual BasicKeyAction<T>& getLeftButtonAction() = 0;
		
		virtual const BasicKeyAction<T>& getLeftButtonAction() const = 0;
		
		virtual BasicKeyAction<T>& getRightButtonAction() = 0;
		
		virtual const BasicKeyAction<T>& getRightButtonAction() const = 0;
		
		void update(sf::Vector2i mousePosition) override;
	};
	
	using IMouseInteraction = IBasicMouseInteraction<>;
}

#include "IBasicMouseInteraction.inl"
