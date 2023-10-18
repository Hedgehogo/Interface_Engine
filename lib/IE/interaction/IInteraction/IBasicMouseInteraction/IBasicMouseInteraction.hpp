#pragma once

#include "../IInteraction.hpp"

namespace ie {
	template<typename T>
	class IBasicMouseInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct IBasicMouseInteraction : public virtual IBasicInteraction<T> {
			ie::IBasicMouseInteraction<T>* make(BasicActionInitInfo<T> init_info) override = 0;
		};
	}
	
	template<typename T = std::monostate>
	class IBasicMouseInteraction : public virtual IBasicInteraction<T> {
	public:
		using Make = make_system::IBasicMouseInteraction<T>;
		
		virtual BasicKeyAction<T>& get_left_button_action() = 0;
		
		virtual const BasicKeyAction<T>& get_left_button_action() const = 0;
		
		virtual BasicKeyAction<T>& get_right_button_action() = 0;
		
		virtual const BasicKeyAction<T>& get_right_button_action() const = 0;
		
		void update(sf::Vector2i mouse_position) override;
	};
	
	using IMouseInteraction = IBasicMouseInteraction<>;
}

#include "IBasicMouseInteraction.inl"
