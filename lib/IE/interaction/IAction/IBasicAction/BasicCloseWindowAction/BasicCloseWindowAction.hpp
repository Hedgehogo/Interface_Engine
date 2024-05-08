#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/interaction/IAction/BasicTouchAction/BasicBaseTouchAction/BasicBaseTouchAction.hpp"

namespace ie {
	template<typename T>
	class BasicCloseWindowAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicCloseWindowAction : public BasicTouchAction<T> {
			auto make(BasicActionInitInfo<T> init_info) -> ie::BasicCloseWindowAction<T>* override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicCloseWindowAction : public BasicBaseTouchAction<T> {
	public:
		using Make = make_system::BasicCloseWindowAction<T>;
		
		BasicCloseWindowAction(Make&& make, BasicActionInitInfo<T> init_info);
		
	protected:
		auto start_pressed() -> void override;
		
		auto stop_pressed() -> void override;
		
		auto while_pressed() -> void override;
		
		auto while_not_pressed() -> void override;
		
		sf::RenderWindow* window_;
	};
	
	using CloseWindowAction = BasicCloseWindowAction<std::monostate>;
}

template<typename T>
struct ieml::Decode<char, ie::BasicCloseWindowAction<T> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BasicCloseWindowAction<T> >;
};

#include "BasicCloseWindowAction.inl"
