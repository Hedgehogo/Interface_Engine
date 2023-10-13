#pragma once

#include "../BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include <functional>

namespace ie {
	template<typename T>
	class BasicFnKeyAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicFnKeyAction : public BasicKeyAction<T> {
			using FnType = std::function<void(sf::Vector2i mousePosition)>;
			
			FnType startPressedFn;
			FnType whilePressedFn;
			FnType stopPressedFn;
			FnType whileNotPressedFn;
			
			BasicFnKeyAction(
				FnType startPressedFn = [](sf::Vector2i) {
				},
				FnType whilePressedFn = [](sf::Vector2i) {
				},
				FnType stopPressedFn = [](sf::Vector2i) {
				},
				FnType whileNotPressedFn = [](sf::Vector2i) {
				}
			);
			
			ie::BasicFnKeyAction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicFnKeyAction : public BasicBaseKeyAction<T> {
	public:
		using FnType = std::function<void(sf::Vector2i mousePosition)>;
		using Make = make_system::BasicFnKeyAction<T>;
		
		BasicFnKeyAction(Make&& make, BasicActionInitInfo<T> initInfo);
		
		BasicFnKeyAction(
			FnType startPressedFn = [](sf::Vector2i) {
			},
			FnType whilePressedFn = [](sf::Vector2i) {
			},
			FnType stopPressedFn = [](sf::Vector2i) {
			},
			FnType whileNotPressedFn = [](sf::Vector2i) {
			}
		);
		
		BasicFnKeyAction<T>* copy() override;
	
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		FnType startPressedFn;
		FnType whilePressedFn;
		FnType stopPressedFn;
		FnType whileNotPressedFn;
	};
	
	using FnKeyAction = BasicFnKeyAction<>;
}

#include "BasicFnKeyAction.inl"