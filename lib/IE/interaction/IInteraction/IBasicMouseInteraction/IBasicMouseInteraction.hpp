#pragma once

#include "../IInteraction.hpp"

namespace ie {
	template<typename T>
	class IBasicMouseInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct IBasicMouseInteraction : public virtual IBasicInteraction<T> {
			auto make(BasicActionInitInfo<T> init_info) -> ie::IBasicMouseInteraction<T>* override = 0;
		};
	}
	
	template<typename T = std::monostate>
	class IBasicMouseInteraction : public virtual IBasicInteraction<T> {
	public:
		using Make = make_system::IBasicMouseInteraction<T>;
		
		virtual auto get_left_button_action() -> BasicKeyAction<T>& = 0;
		
		virtual auto get_left_button_action() const -> BasicKeyAction<T> const& = 0;
		
		virtual auto get_right_button_action() -> BasicKeyAction<T>& = 0;
		
		virtual auto get_right_button_action() const -> BasicKeyAction<T> const& = 0;
		
		auto update(sf::Vector2i mouse_position) -> void override;
	};
	
	using IMouseInteraction = IBasicMouseInteraction<>;
}

#include "IBasicMouseInteraction.inl"
