#pragma once

#include <SFML/System/Vector2.hpp>
#include "../IAction.hpp"
#include "../../BasicActionInitInfo/BasicActionInitInfo.hpp"

namespace ie {
	template<typename T>
	class BasicKeyAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicKeyAction {
			virtual ie::BasicKeyAction<T>* make(BasicActionInitInfo<T> init_info) = 0;
			
			virtual ~BasicKeyAction() = default;
		};
	}
	
	template<typename T = std::monostate>
	class BasicKeyAction : public virtual IAction {
	public:
		using Make = make_system::BasicKeyAction<T>;
		
		explicit BasicKeyAction();
		
		virtual void init(BasicActionInitInfo<T> init_info);
		
		virtual void set_pressed(bool pressed);
		
		virtual void update(sf::Vector2i mouse_position, bool press) = 0;
		
		virtual BasicKeyAction* copy() = 0;
	
	protected:
		bool pressed;
	};
	
	using KeyAction = BasicKeyAction<std::monostate>;
}

#include "BasicKeyAction.inl"