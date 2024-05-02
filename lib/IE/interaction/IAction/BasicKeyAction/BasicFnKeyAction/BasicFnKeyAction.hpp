#pragma once

#include "../BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include <functional>

namespace ie {
	template<typename T>
	class BasicFnKeyAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicFnKeyAction : public BasicKeyAction<T> {
			using FnType = std::function<void(sf::Vector2i point_position)>;
			
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
			
			auto make(BasicActionInitInfo<T> init_info) -> ie::BasicFnKeyAction<T>* override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicFnKeyAction : public BasicBaseKeyAction<T> {
	public:
		using FnType = std::function<void(sf::Vector2i point_position)>;
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
		
	protected:
		auto start_pressed() -> void override;
		
		auto stop_pressed() -> void override;
		
		auto while_pressed() -> void override;
		
		auto while_not_pressed() -> void override;
		
		FnType start_pressed_fn_;
		FnType while_pressed_fn_;
		FnType stop_pressed_fn_;
		FnType while_not_pressed_fn_;
	};
	
	using FnKeyAction = BasicFnKeyAction<>;
}

#include "BasicFnKeyAction.inl"