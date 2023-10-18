#pragma once

#include "../BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include <functional>

namespace ie {
	template<typename T>
	class BasicFnKeyAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicFnKeyAction : public BasicKeyAction<T> {
			using FnType = std::function<void(sf::Vector2i mouse_position)>;
			
			FnType start_pressed_fn;
			FnType while_pressed_fn;
			FnType stop_pressed_fn;
			FnType while_not_pressed_fn;
			
			BasicFnKeyAction(
				FnType start_pressed_fn = [](sf::Vector2i) {
				},
				FnType while_pressed_fn = [](sf::Vector2i) {
				},
				FnType stop_pressed_fn = [](sf::Vector2i) {
				},
				FnType while_not_pressed_fn = [](sf::Vector2i) {
				}
			);
			
			ie::BasicFnKeyAction<T>* make(BasicActionInitInfo<T> init_info) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicFnKeyAction : public BasicBaseKeyAction<T> {
	public:
		using FnType = std::function<void(sf::Vector2i mouse_position)>;
		using Make = make_system::BasicFnKeyAction<T>;
		
		BasicFnKeyAction(Make&& make, BasicActionInitInfo<T> init_info);
		
		BasicFnKeyAction(
			FnType start_pressed_fn = [](sf::Vector2i) {
			},
			FnType while_pressed_fn = [](sf::Vector2i) {
			},
			FnType stop_pressed_fn = [](sf::Vector2i) {
			},
			FnType while_not_pressed_fn = [](sf::Vector2i) {
			}
		);
		
		BasicFnKeyAction<T>* copy() override;
	
	protected:
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		FnType start_pressed_fn;
		FnType while_pressed_fn;
		FnType stop_pressed_fn;
		FnType while_not_pressed_fn;
	};
	
	using FnKeyAction = BasicFnKeyAction<>;
}

#include "BasicFnKeyAction.inl"