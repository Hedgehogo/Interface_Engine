#pragma once

#include "../BasicKeyAction.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicBaseKeyAction : public virtual BasicKeyAction<T> {
	public:
		BasicBaseKeyAction() = default;
		
		void init(BasicActionInitInfo<T> init_info) override;
		
		void set_pressed(bool pressed) override;
		
		void update(sf::Vector2i mouse_position, bool press) override;
	
	protected:
		virtual void start_pressed() = 0;
		
		virtual void stop_pressed() = 0;
		
		virtual void while_pressed() = 0;
		
		virtual void while_not_pressed() = 0;
		
		sf::Vector2i mouse_position;
	};
	
	using BaseKeyAction = BasicBaseKeyAction<>;
}

#include "BasicBaseKeyAction.inl"
