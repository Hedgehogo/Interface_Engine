#pragma once

#include <string>
#include "IE/interaction/IAction/BasicTouchAction/BasicBaseTouchAction/BasicBaseTouchAction.hpp"
#include "IE/ieml/shortcuts/shortcuts.hpp"

namespace ie {
	template<typename T>
	class BasicOpenUrlAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicOpenUrlAction : public BasicTouchAction<T> {
			std::string url;
			
			BasicOpenUrlAction(std::string url);
			
			auto make(BasicActionInitInfo<T> init_info) -> ie::BasicOpenUrlAction<T>* override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicOpenUrlAction : public BasicBaseTouchAction<T> {
	public:
		using Make = make_system::BasicOpenUrlAction<T>;
		
		BasicOpenUrlAction(Make&& make, BasicActionInitInfo<T> init_info);
		
		BasicOpenUrlAction(std::string url);
		
	protected:
		auto start_pressed() -> void override;
		
		auto stop_pressed() -> void override;
		
		auto while_pressed() -> void override;
		
		auto while_not_pressed() -> void override;
		
		std::string url_;
	};
	
	using OpenUrlAction = BasicOpenUrlAction<>;
	
	auto determine_url(ieml::Node const& node) -> bool;
}

template<typename T>
struct ieml::Decode<char, ie::make_system::BasicOpenUrlAction<T> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicOpenUrlAction<T> >;
};

#include "BasicOpenUrlAction.inl"